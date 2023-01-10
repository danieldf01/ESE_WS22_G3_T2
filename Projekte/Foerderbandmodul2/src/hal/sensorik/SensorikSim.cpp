/*
 * SensorikSim.cpp
 *
 *  Created on: Dec 8, 2022
 *      Author: bardi
 */

#include "SensorikSim.h"

SensorikSim::SensorikSim(OutputDispatcher &dispatcher, HALAktorik &halaktorik) {
	connector = new SensorikQnet();
	gpioSetup = new GPIOSetup();
	outputDispatcher = &dispatcher;
	aktorik = &halaktorik;
	interruptID = 0;

	// For ADC
	adcBaseAddr = 0;
	interruptIDADC = 0;

	// For the ADC output
	count = 0;
	adcSum = 0;
	adcAverage = 0;
}

SensorikSim::~SensorikSim() {
	connector->~SensorikQnet();
	gpioSetup->~GPIOSetup();
	outputDispatcher->~OutputDispatcher();
	aktorik->~HALAktorik();
}

int SensorikSim::runHALSteuerung(){

	ThreadCtl(_NTO_TCTL_IO, 0);	//Request IO privileges for process.
	// Request interrupt and IO abilities.
	gpioSetup->requestGPIOAbiltiys();
	InterruptEnable();	//Enables interrupts.

	adcBaseAddr = mmap_device_io(ADC_LENGTH, ADC_BASE); //Setup global ADC base address. todo hinzugekommen

	// Qnet Channel erstellen und verbinden
	int chanID = connector->createConnection();
	int conID = connector->openConnection(chanID);

	attachInterrupts(conID);

	uintptr_t port0BaseAddr = mmap_device_io(GPIO_REGISTER_LENGHT, GPIO_PORT0);
	//gpioSetup->configGPIOIRQEventTypes(port0BaseAddr);
	setupGPIO(port0BaseAddr);
	uintptr_t gpioBase = mmap_device_io(GPIO_REGISTER_LENGHT, GPIO_PORT0);
	int current_level = (in32((uintptr_t) gpioBase + GPIO_DATAIN) >> 14) & 0x1;
	if(current_level==0){
		outputDispatcher->dispatchOutput(WEICHE2, 0);
	}
	else{
		outputDispatcher->dispatchOutput(AUSWERFER2, 0);
	}

	/* ### Start sampling ### */
	adc_clear_interrupt();		//clear interrupt (just in case)
	adc_enable_interrupt();		//enable interrupt
	adc_ctrl_start_sample();	//start sampling

	/* ### Start thread for handling interrupt messages. */
	receivingRoutine(chanID);

	// ENDE
	connector->closeConnection(conID);
	connector->destroyConnection(chanID);

	return EXIT_SUCCESS;
}

void SensorikSim::attachInterrupts(int conID){
	/* ### Register interrupts by OS. ### */
	struct sigevent intr_event;
	SIGEV_PULSE_INIT(&intr_event, conID, SIGEV_PULSE_PRIO_INHERIT, PULSE_INTR_ON_PORT0, 0);
	interruptID = InterruptAttachEvent(INTR_GPIO_PORT0, &intr_event, 0);
	if (interruptID < 0) {
		perror("Interrupt was not able to be attached!");
	}

	struct sigevent event;
	/* ### Setup interrupt ### */
	SIGEV_PULSE_INIT(&event, conID, SIGEV_PULSE_PRIO_INHERIT,PULSE_ADC_SAMLING_DONE, 0);

	/* Attach ISR  */
	int interruptIDADC = InterruptAttachEvent(INTER_ADC, &event, 0);
	if (interruptIDADC == -1) {
		perror("InterruptAttach failed!");
		exit(EXIT_FAILURE);
	}
}

void SensorikSim::receivingRoutine(int channelID) {
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

				uint32_t value = adc_read_sample_data();
				adc_clear_interrupt();
				InterruptUnmask(INTER_ADC, interruptIDADC);

				// Sample direkt damit der naechste Interrupt vor dem Print gemacht wird!
				adc_ctrl_start_sample();	//Start next sampling.

				// Handle ein ADC Interrupt
//				int messung = window(msg.value.sival_int);
				int messung = value;// Wert direkt

				if(messung != -1){
//					cout << "BEFORE SEND" << messung << endl;
					outputDispatcher->dispatchADC(messung);
				}
			}
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

void SensorikSim::adc_enable_interrupt(void){
	out32((uintptr_t) adcBaseAddr + ADC_IRQ_ENABLE_SET, ADC_IRQ_PIN_MASK);
}


void SensorikSim::adc_disable_interrupt(void){
	out32((uintptr_t) adcBaseAddr + ADC_IRQ_ENABLE_CLR, ADC_IRQ_PIN_MASK);
}


void SensorikSim::adc_clear_interrupt(void){
	out32((uintptr_t) adcBaseAddr + ADC_IRQ_STATUS, ADC_IRQ_PIN_MASK);
}


void SensorikSim::adc_ctrl_start_sample(void){
	out32((uintptr_t) adcBaseAddr + ADC_CTRL, 0x1);
}

uint32_t SensorikSim::adc_read_sample_data(void){
	return in32((uintptr_t) adcBaseAddr + ADC_DATA);
}

void SensorikSim::setupGPIO(uintptr_t port0BaseAddr){
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
}
