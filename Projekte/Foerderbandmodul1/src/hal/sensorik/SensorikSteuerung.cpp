/*
 * HALSteuerung.cpp
 *
 *  Created on: 15.11.2022
 *      Author: Tobias Thoelen
 */

#include "SensorikSteuerung.h"
using namespace std;

SensorikSteuerung::SensorikSteuerung(OutputDispatcher &dispatcher, HALAktorik &halaktorik) {
	connector = new SensorikQnet();
	gpioSetup = new GPIOSetup();
	outputDispatcher = &dispatcher;
	aktorik = &halaktorik;
	interruptID = 0;
	// For ADC
	tsc = new TSCADC();
	adc = new ADC(*tsc);

	// For the ADC output
	count = 0;
	adcSum = 0;
	adcAverage = 0;
}

SensorikSteuerung::~SensorikSteuerung() {
	connector->~SensorikQnet();
	gpioSetup->~GPIOSetup();
	outputDispatcher->~OutputDispatcher();
	aktorik->~HALAktorik();
	adc->~ADC();
	tsc->~TSCADC();
}

void SensorikSteuerung::runHALSteuerung(){

	/* Build Up */
	ThreadCtl(_NTO_TCTL_IO, 0);	//Request IO privileges for process.
	gpioSetup->requestGPIOAbiltiys();
	InterruptEnable();			//Enables interrupts.

	// Qnet Channel erstellen und verbinden
	int chanID = connector->createConnection();
	int conID = connector->openConnection(chanID);

	attachInterrupts(conID);

	uintptr_t port0BaseAddr = mmap_device_io(GPIO_REGISTER_LENGHT, GPIO_PORT0);
	gpioSetup->configGPIOIRQEventTypes(port0BaseAddr);

	// start Thread
	//thread receivingThread = thread(&SensorikSteuerung::receivingRoutine, this, chanID, adc);
	// start Sample

	uintptr_t gpioBase = mmap_device_io(GPIO_REGISTER_LENGHT, GPIO_PORT0);
	int current_level = (in32((uintptr_t) gpioBase + GPIO_DATAIN) >> 27) & 0x1;
	if(current_level==0){
		aktorik->eStopp();
		outputDispatcher->dispatchOutput(27,0);
	}

	adc->sample();
	receivingRoutine(chanID, adc);
	// TODO Still needed?
	//detachInterrupts(adc);

	/* Clean Up */

	// TODO stop Thread still needed?
	//receivingThread.join();
	//MsgSendPulse(conID, -1, PULSE_STOP_THREAD, 0); //using prio of calling thread.
	//receivingThread.join();

	// shutdown Connection
	connector->closeConnection(conID);
	connector->destroyConnection(chanID);
}

ADC* SensorikSteuerung::attachInterrupts(int conID){

	// Fuer die GPIO Pins
	struct sigevent intr_event;
	SIGEV_PULSE_INIT(&intr_event, conID, SIGEV_PULSE_PRIO_INHERIT, PULSE_INTR_ON_PORT0, 0);
	interruptID = InterruptAttachEvent(INTR_GPIO_PORT0, &intr_event, 0);
	if (interruptID < 0) {
		perror("Interrupt was not able to be attached!");
		// TODO Anpassen
	}

	// Fuer den ADC
	adc->registerAdcISR(conID, PULSE_ADC_SAMLING_DONE);
	return adc;
}

void  SensorikSteuerung::detachInterrupts(ADC *adc){
	int intr_detach_status = InterruptDetach(interruptID);
	if (intr_detach_status != EOK) {
		perror("Detaching interrupt failed!");
		exit(EXIT_FAILURE);
	}
	adc->adcDisable();
	adc->unregisterAdcISR();
}

void SensorikSteuerung::receivingRoutine(int channelID, ADC *adc) {
	ThreadCtl( _NTO_TCTL_IO, 0);	//Request IO privileges

	//_pulse msg;
	receivingRunning = true;

	while (receivingRunning) {
		_pulse msg;
		int recvid = MsgReceivePulse(channelID, &msg, sizeof(_pulse), nullptr);

		if (recvid < 0) {
			perror("MsgReceivePulse failed!");
			exit(EXIT_FAILURE);
		}

		if (recvid == 0) {	//pulse received.

			//Stop thread while it blocks.
			if (msg.code == PULSE_STOP_THREAD) {
				receivingRunning = false;
			}

			// Handle alle Interrupts ausser von dem ADC
			if (msg.code == PULSE_INTR_ON_PORT0){
				handleInterrupt();
			}

			//ADC interrupt value.
			if (msg.code == PULSE_ADC_SAMLING_DONE) {
				// Sample direkt damit der naechste Interrupt vor dem Print gemacht wird!
				adc->sample();
				// Handle ein ADC Interrupt
				int messung = window(msg.value.sival_int);
							if(messung != -1){
								outputDispatcher->dispatchADC(messung, 1);
							}
			}

			// Do not ignore OS pulses!
		}
	}
}

typedef struct interuptet_pin {
	int pin;
	int current_level;
} interuptet_pin;

void SensorikSteuerung::handleInterrupt(void) {
	uintptr_t gpioBase = mmap_device_io(GPIO_REGISTER_LENGHT, GPIO_PORT0);

	unsigned int intrStatusReg = in32(uintptr_t(gpioBase + GPIO_IRQSTATUS_1));

	out32(uintptr_t(gpioBase + GPIO_IRQSTATUS_1), 0xffffffff);	//clear all interrupts.
	InterruptUnmask(INTR_GPIO_PORT0, interruptID);				//unmask interrupt.

	for (int pin = 31; pin >= 0; pin--) {
		unsigned int mask = (uint32_t) BIT_MASK(pin);
		if (intrStatusReg == mask) {
			int current_level = (in32((uintptr_t) gpioBase + GPIO_DATAIN) >> pin) & 0x1;
			if (pin == E_STOP_PIN && current_level == 0){
				aktorik->eStopp();
			}
			// Hier die Dispatcher GPIO Methode
			outputDispatcher->dispatchOutput(pin, current_level);
		}
	}
}

void SensorikSteuerung::handleADCInterrupt(_pulse *msg) {
	//printf("%d\n",);
	//cout << msg->value.sival_int << endl;

	// Get every 100 values
	count++;
	adcSum = adcSum + msg->value.sival_int;

	if (count == 100) {
		adcAverage = adcSum / count;
		// Hier die Dispatcher ADC Schnittstelle von der HAL aus
		outputDispatcher->dispatchADC(adcAverage,1);
		//cout << adcAverage << endl;
		// reset count and adcSum
		count = 0;
		adcSum = 0;
	}
}
int SensorikSteuerung::window(const int messung) {
	static int i = 1;
	static int messung_mean = 0;
	int ret = -1;
	if(i < WINDOW_SIZE){
		messung_mean += messung;
		i++;
	}else{
		i=1;
		messung_mean += messung;
		messung_mean = messung_mean / WINDOW_SIZE;
		ret = messung_mean;
		messung_mean = 0;
	}
	return ret;
}
