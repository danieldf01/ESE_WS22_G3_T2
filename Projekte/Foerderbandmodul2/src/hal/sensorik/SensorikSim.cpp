/*
 * SensorikSim.cpp
 *
 *  Created on: Dec 8, 2022
 *      Author: bardi
 */

#include "SensorikSim.h"

SensorikSim::SensorikSim(OutputDispatcher &dispatcher, HALAktorik &halaktorik) {
	// TODO Auto-generated constructor stub
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

SensorikSim::~SensorikSim() {
	// TODO Auto-generated destructor stub
		outputDispatcher->~OutputDispatcher();
		aktorik->~HALAktorik();
		adc->~ADC();
		tsc->~TSCADC();
}

int SensorikSim::runHALSteuerung(){

	/* ### Setup ### */
	ThreadCtl(_NTO_TCTL_IO, 0);	//Request IO privileges for process.

	// Request interrupt and IO abilities.
	int procmgr_status = procmgr_ability(
			0,
			PROCMGR_ADN_ROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_INTERRUPT,
			PROCMGR_ADN_NONROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_INTERRUPT,
			PROCMGR_ADN_ROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_IO,
			PROCMGR_ADN_NONROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_IO,
			PROCMGR_AID_EOL
	);
	if(procmgr_status != EOK){
		perror("Requested abilities failed or denied!");
		exit(EXIT_FAILURE);
	}

	InterruptEnable();			//Enables interrupts.

	/* ### Create channel ### */
	int chanID = ChannelCreate(0);//Create channel to receive interrupt pulse messages.
	if (chanID < 0) {
		perror("Could not create a channel!\n");
		return EXIT_FAILURE;
	}

	int conID = ConnectAttach(0, 0, chanID, _NTO_SIDE_CHANNEL, 0); //Connect to channel.
	if (conID < 0) {
		perror("Could not connect to channel!");
		return EXIT_FAILURE;
	}

	/* ### Register interrupts by OS. ### */
	struct sigevent intr_event;
	SIGEV_PULSE_INIT(&intr_event, conID, SIGEV_PULSE_PRIO_INHERIT, PULSE_INTR_ON_PORT0, 0);
	interruptID = InterruptAttachEvent(INTR_GPIO_PORT0, &intr_event, 0);
	if (interruptID < 0) {
		perror("Interrupt was not able to be attached!");
		return EXIT_FAILURE;
	}

	/* ### Configure registers to receive irq events. */
	uintptr_t port0BaseAddr = mmap_device_io(GPIO_REGISTER_LENGHT, GPIO_PORT0);



	// Set irq event types.
	unsigned int temp;
	// Enable interrupts on pins.
	temp = (
			BIT_MASK(LS_ANFANG_PIN) |
			BIT_MASK(HS_HOCH_OK_PIN) |
			BIT_MASK(LS_SEPERATOR_PIN) |
			BIT_MASK(METALLSENSOR_PIN) |
			BIT_MASK(LS_ZUSTAND_SEPERATOR_PIN) |
			BIT_MASK(LS_RUTSCHE_PIN) |
			BIT_MASK(LS_ENDE_PIN) |
			BIT_MASK(T_START_PIN) |
			BIT_MASK(T_STOP_PIN) |
			BIT_MASK(T_RESET_PIN) |
			BIT_MASK(E_STOP_PIN)
	);//Add desired pins.
	out32((uintptr_t) port0BaseAddr + GPIO_IRQSTATUS_SET_1, temp);



	//	(for rising edge detection)
	temp = in32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT));			//Read current config.
	temp |= (
			BIT_MASK(LS_ANFANG_PIN) |
			BIT_MASK(HS_HOCH_OK_PIN) |
			BIT_MASK(LS_SEPERATOR_PIN) |
			BIT_MASK(METALLSENSOR_PIN) |
			BIT_MASK(LS_ZUSTAND_SEPERATOR_PIN) |
			BIT_MASK(LS_RUTSCHE_PIN) |
			BIT_MASK(LS_ENDE_PIN) |
			BIT_MASK(T_START_PIN) |
			BIT_MASK(T_STOP_PIN) |
			BIT_MASK(T_RESET_PIN) |
			BIT_MASK(E_STOP_PIN)
	);//Add desired pins.

	out32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT), temp);			//Write new config back.

	// 	(for falling edge detection)
	temp = in32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT));			//Read current config.
	temp |= (
			BIT_MASK(LS_ANFANG_PIN) |
			BIT_MASK(HS_HOCH_OK_PIN) |
			BIT_MASK(LS_SEPERATOR_PIN) |
			BIT_MASK(METALLSENSOR_PIN) |
			BIT_MASK(LS_ZUSTAND_SEPERATOR_PIN) |
			BIT_MASK(LS_RUTSCHE_PIN) |
			BIT_MASK(LS_ENDE_PIN) |
			BIT_MASK(T_START_PIN) |
			BIT_MASK(T_STOP_PIN) |
			BIT_MASK(T_RESET_PIN) |
			BIT_MASK(E_STOP_PIN)
	);//Add desired pins.
	out32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT), temp);			//Write new config back.

	/* ### Start thread for handling interrupt messages. */
	adc->sample();
	receivingRoutine(chanID,adc);

	/* ### Cleaning up. */

	// Detach interrupts.
	int intr_detach_status = InterruptDetach(interruptID);
	if(intr_detach_status != EOK){
		perror("Detaching interrupt failed!");
		exit(EXIT_FAILURE);
	}


	// Reset registers.
	// ONLY IF YOUR THE ONLY PROGRAM WITH INTERRUPTS RUNNING ON THIS MACHINE!

	// Close channel
	int detach_status = ConnectDetach(conID);
	if(detach_status != EOK){
		perror("Detaching channel failed!");
		exit(EXIT_FAILURE);
	}

	int destroy_status = ChannelDestroy(chanID);
	if(destroy_status != EOK){
		perror("Destroying channel failed!");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
void SensorikSim::receivingRoutine(int channelID, ADC *adc) {

	//ThreadCtl( _NTO_TCTL_IO, 0);	//Request IO privileges

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
					outputDispatcher->dispatchADC(messung);
				}
			}

			// Do not ignore OS pulses!
		}
	}

	printf("Message thread stops...\n");
}


typedef struct interuptet_pin {
	int pin;
	int current_level;
} interuptet_pin;

void SensorikSim::handleInterrupt(void) {
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
			//printf("Interrupt on pin %d, now %d\n", pin, current_level);
			outputDispatcher->dispatchOutput(pin, current_level);
			// TODO Hier die Dispatcher GPIO Methode
		}
	}
}
void SensorikSim::handleADCInterrupt(_pulse *msg) {


	// Get every 100 values
	count++;
	adcSum = adcSum + msg->value.sival_int;

	if (count == 100) {
		adcAverage = adcSum / count;
		// TODO Hier die Dispatcher ADC Schnittstelle von der HAL aus
		outputDispatcher->dispatchADC(adcAverage);
		//cout << adcAverage << endl;
		// reset count and adcSum
		count = 0;
		adcSum = 0;
	}
}
int SensorikSim::window(const int messung) {
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
