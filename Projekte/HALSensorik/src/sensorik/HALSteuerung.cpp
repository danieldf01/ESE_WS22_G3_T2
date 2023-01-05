/*
 * HALSteuerung.cpp
 *
 *  Created on: 15.11.2022
 *      Author: User
 */

#include "HALSteuerung.h"

HALSteuerung::HALSteuerung() {
	connector = new QnetHandler();
	gpioSetup = new GPIOSetup();
}

HALSteuerung::~HALSteuerung() {
	// TODO Auto-generated destructor stub
}

void HALSteuerung::runHALSteuerung(){

	/* Build Up */
	ThreadCtl(_NTO_TCTL_IO, 0);	//Request IO privileges for process.
	gpioSetup->requestGPIOAbiltiys();
	InterruptEnable();			//Enables interrupts.
	//int chanID = connector->createConnection();
	//this->conID = connector->openConnection(&chanID);

	int chanID = ChannelCreate(0);
	this->conID = ConnectAttach(0, 0, chanID, _NTO_SIDE_CHANNEL, 0);

	ADC *adc = attachInterrupts();

	uintptr_t port0BaseAddr = mmap_device_io(GPIO_REGISTER_LENGHT, GPIO_PORT0);
	gpioSetup->configGPIOIRQEventTypes(port0BaseAddr);

	// start Thread
	thread receivingThread = thread(&HALSteuerung::receivingRoutine, this, chanID, adc);

	adc->sample();
	detachInterrupts(adc);

	/* Clean Up */

	// stop Thread
	MsgSendPulse(conID, -1, PULSE_STOP_THREAD, 0); //using prio of calling thread.
	receivingThread.join();

	// shutdown Connection
	connector->closeConnection(&conID);
	connector->destroyConnection(&chanID);
}

ADC* HALSteuerung::attachInterrupts(){
	// For GPIO
	struct sigevent intr_event;
	SIGEV_PULSE_INIT(&intr_event, conID, SIGEV_PULSE_PRIO_INHERIT, PULSE_INTR_ON_PORT0, 0);
	interruptID = InterruptAttachEvent(INTR_GPIO_PORT0, &intr_event, 0);
	if (interruptID < 0) {
		perror("Interrupt was not able to be attached!");
		// TODO Anpassen
	}
	// For ADC
	TSCADC tsc;
	ADC* adc = new ADC(tsc);
	adc->registerAdcISR(conID, PULSE_ADC_SAMLING_DONE);
	return adc;
}

void  HALSteuerung::detachInterrupts(ADC *adc){
	int intr_detach_status = InterruptDetach(interruptID);
	if (intr_detach_status != EOK) {
		perror("Detaching interrupt failed!");
		exit(EXIT_FAILURE);
	}
	adc->adcDisable();
	adc->unregisterAdcISR();
}

void HALSteuerung::receivingRoutine(int channelID, ADC *adc) {

	ThreadCtl( _NTO_TCTL_IO, 0);	//Request IO privileges

	_pulse msg;
	receivingRunning = true;

	printf("Message thread started.\n");

	while (receivingRunning) {
		int recvid = MsgReceivePulse(channelID, &msg, sizeof(_pulse), nullptr);

		if (recvid < 0) {
			perror("MsgReceivePulse failed!");
			exit(EXIT_FAILURE);
		}

		if (recvid == 0) {	//pulse received.

			//Stop thread while it blocks.
			if (msg.code == PULSE_STOP_THREAD) {
				printf("Thread kill code received!\n");
				receivingRunning = false;
			}

			if (msg.code == PULSE_INTR_ON_PORT0){
				handleInterrupt();
			}

			//ADC interrupt value.
			if (msg.code == PULSE_ADC_SAMLING_DONE) {
				printf("%d\n", msg.value);
				adc->sample();
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

void HALSteuerung::handleInterrupt(void) {
	uintptr_t gpioBase = mmap_device_io(GPIO_REGISTER_LENGHT, GPIO_PORT0);

	unsigned int intrStatusReg = in32(uintptr_t(gpioBase + GPIO_IRQSTATUS_1));

	out32(uintptr_t(gpioBase + GPIO_IRQSTATUS_1), 0xffffffff);	//clear all interrupts.
	InterruptUnmask(INTR_GPIO_PORT0, interruptID);				//unmask interrupt.

	for (int pin = 0; pin < 32; pin++) {
		unsigned int mask = (uint32_t) BIT_MASK(pin);
		if (intrStatusReg == mask) {
			int current_level = (in32((uintptr_t) gpioBase + GPIO_DATAIN) >> pin) & 0x1;
			printf("Interrupt on pin %d, now %d\n", pin, current_level);
		}
	}
}
