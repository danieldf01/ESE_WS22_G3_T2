/**
 * InterruptDemo.cpp
 *
 *  Created on: 08.11.2021
 *      Author: Bjoern Dittmann
 *
 * Demonstriert das handling von Interrupts mittels pulse messages
 * (InterruptAttachEvent).
 *
 *
 */

//#include <stdio.h>
//#include <errno.h>
//#include <sys/neutrino.h>
//#include <sys/procmgr.h>
//#include <iostream>
//#include <thread>
//#include <chrono>
//
//#include "simqnxgpioapi.h"
//#include "simqnxirqapi.h"


/* Code configuration */
#define DEMO true			//true for demo time, false to spin forever.
#define DEMO_DURATION 1		//Duration of demo time in minutes.


/* Interrupt numbers  (spruh73l.pdf S.465 ff.) */
#define INTR_GPIO_PORT0 97
#define INTR_GPIO_PORT1 99
#define INTR_GPIO_PORT2 33


/* GPIO port addresses (spruh73l.pdf S.177 ff.) */
#define GPIO_PORT0 0x44E07000
#define GPIO_PORT1 0x4804C000
#define GPIO_PORT2 0x481AC000


/* GPIO port registers length */
#define GPIO_REGISTER_LENGHT 0x1000


/* GPIO register offsets (spruh73l.pdf S.4877) */
#define GPIO_LEVELDETECT0 0x140
#define GPIO_LEVELDETECT1 0x144
#define GPIO_RISINGDETECT 0x148
#define GPIO_FALLINGDETECT 0x14C

#define GPIO_IRQSTATUS_0 0x2C
#define GPIO_IRQSTATUS_1 0x30
#define GPIO_IRQSTATUS_SET_0 0x34
#define GPIO_IRQSTATUS_SET_1 0x38

#define GPIO_DATAIN 0x138
#define GPIO_SETDATAOUT 0x194


/* Actuators pin mapping */
#define MOTOR_RIGHT_PIN 12
#define SORTIERER_PIN 19


/* Sensors pin mapping (Aufgabenbeschreibung o. Schaltplan) */
#define LS_ANFANG_PIN 2		//active low
#define HS_HOCH_OK_PIN 4	//active high
#define LS_SEPERATOR_PIN 5	//active low
#define METALLSENSOR_PIN 7	//active high
#define LS_ZUSTAND_SEPERATOR_PIN 14	//active high
#define LS_RUTSCHE_PIN 15	//active low
#define LS_ENDE_PIN 20		//active low
#define T_START_PIN  22		//active high
#define T_STOP_PIN 23		//active low
#define T_RESET_PIN 26		//active high
#define E_STOP_PIN 27		//active low

/* Helper macros */
#define BIT_MASK(x) (0x1 << (x))


/* My pulse codes */
#define PULSE_STOP_THREAD _PULSE_CODE_MINAVAIL + 1
#define PULSE_INTR_ON_PORT0 _PULSE_CODE_MINAVAIL + 2


/* Prototypes*/
int main(int argc, char** args);
void receivingRoutine(int);
void handleInterrupt();


/* Variables */
bool receivingRunning = false;
int interruptID;


/* Implementation */
using namespace std;

int main(int argc, char** args) {

	/* ### Setup ### */
//	ThreadCtl(_NTO_TCTL_IO, 0);	//Request IO privileges for process.

	// Request interrupt and IO abilities.
//	int procmgr_status = procmgr_ability(
//		0,
//		PROCMGR_ADN_ROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_INTERRUPT,
//		PROCMGR_ADN_NONROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_INTERRUPT,
//		PROCMGR_ADN_ROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_IO,
//		PROCMGR_ADN_NONROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_IO,
//		PROCMGR_AID_EOL
//	);
//	if(procmgr_status != EOK){
//		perror("Requested abilities failed or denied!");
//		exit(EXIT_FAILURE);
//	}

//	InterruptEnable();			//Enables interrupts.

	/* ### Create channel ### */
//	int chanID = ChannelCreate(0);//Create channel to receive interrupt pulse messages.
//	if (chanID < 0) {
//		perror("Could not create a channel!\n");
//		return EXIT_FAILURE;
//	}
//
//	int conID = ConnectAttach(0, 0, chanID, _NTO_SIDE_CHANNEL, 0); //Connect to channel.
//	if (conID < 0) {
//		perror("Could not connect to channel!");
//		return EXIT_FAILURE;
//	}

	/* ### Register interrupts by OS. ### */
//	struct sigevent intr_event;
//	SIGEV_PULSE_INIT(&intr_event, conID, SIGEV_PULSE_PRIO_INHERIT, PULSE_INTR_ON_PORT0, 0);
//	interruptID = InterruptAttachEvent(INTR_GPIO_PORT0, &intr_event, 0);
//	if (interruptID < 0) {
//		perror("Interrupt was not able to be attached!");
//		return EXIT_FAILURE;
//	}

	/* ### Configure registers to receive irq events. */
//	uintptr_t port0BaseAddr = mmap_device_io(GPIO_REGISTER_LENGHT, GPIO_PORT0);



//	// Set irq event types.
//	unsigned int temp;
//	// Enable interrupts on pins.
//	temp = (
//			BIT_MASK(LS_ANFANG_PIN) |
//			BIT_MASK(HS_HOCH_OK_PIN) |
//			BIT_MASK(LS_SEPERATOR_PIN) |
//			BIT_MASK(METALLSENSOR_PIN) |
//			BIT_MASK(LS_ZUSTAND_SEPERATOR_PIN) |
//			BIT_MASK(LS_RUTSCHE_PIN) |
//			BIT_MASK(LS_ENDE_PIN) |
//			BIT_MASK(T_START_PIN) |
//			BIT_MASK(T_STOP_PIN) |
//			BIT_MASK(T_RESET_PIN) |
//			BIT_MASK(E_STOP_PIN)
//			);//Add desired pins.
//	out32((uintptr_t) port0BaseAddr + GPIO_IRQSTATUS_SET_1, temp);
//
//
//
//	//	(for rising edge detection)
//	temp = in32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT));			//Read current config.
//	temp |= (
//			BIT_MASK(LS_ANFANG_PIN) |
//			BIT_MASK(HS_HOCH_OK_PIN) |
//			BIT_MASK(LS_SEPERATOR_PIN) |
//			BIT_MASK(METALLSENSOR_PIN) |
//			BIT_MASK(LS_ZUSTAND_SEPERATOR_PIN) |
//			BIT_MASK(LS_RUTSCHE_PIN) |
//			BIT_MASK(LS_ENDE_PIN) |
//			BIT_MASK(T_START_PIN) |
//			BIT_MASK(T_STOP_PIN) |
//			BIT_MASK(T_RESET_PIN) |
//			BIT_MASK(E_STOP_PIN)
//			);//Add desired pins.
//
//	out32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT), temp);			//Write new config back.
//
//	// 	(for falling edge detection)
//	temp = in32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT));			//Read current config.
//	temp |= (
//			BIT_MASK(LS_ANFANG_PIN) |
//			BIT_MASK(HS_HOCH_OK_PIN) |
//			BIT_MASK(LS_SEPERATOR_PIN) |
//			BIT_MASK(METALLSENSOR_PIN) |
//			BIT_MASK(LS_ZUSTAND_SEPERATOR_PIN) |
//			BIT_MASK(LS_RUTSCHE_PIN) |
//			BIT_MASK(LS_ENDE_PIN) |
//			BIT_MASK(T_START_PIN) |
//			BIT_MASK(T_STOP_PIN) |
//			BIT_MASK(T_RESET_PIN) |
//			BIT_MASK(E_STOP_PIN)
//			);//Add desired pins.
//	out32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT), temp);			//Write new config back.

	/* ### Start thread for handling interrupt messages. */
//	thread receivingThread = thread(&receivingRoutine, chanID);

	/* ### Cleaning up. */

	// Detach interrupts.
//	int intr_detach_status = InterruptDetach(interruptID);
//	if(intr_detach_status != EOK){
//		perror("Detaching interrupt failed!");
//		exit(EXIT_FAILURE);
//	}

	// Stop receiving thread.
//	MsgSendPulse(conID, -1, PULSE_STOP_THREAD, 0); //using prio of calling thread.
//	receivingThread.join();

	// Reset registers.
		// ONLY IF YOUR THE ONLY PROGRAM WITH INTERRUPTS RUNNING ON THIS MACHINE!

	// Close channel
//	int detach_status = ConnectDetach(conID);
//	if(detach_status != EOK){
//		perror("Detaching channel failed!");
//		exit(EXIT_FAILURE);
//	}

//	int destroy_status = ChannelDestroy(chanID);
//	if(destroy_status != EOK){
//		perror("Destroying channel failed!");
//		exit(EXIT_FAILURE);
//	}
//
//	return EXIT_SUCCESS;
//}

//void receivingRoutine(int channelID) {
//
//	ThreadCtl( _NTO_TCTL_IO, 0);	//Request IO privileges
//
//	_pulse msg;
//	receivingRunning = true;
//
//	printf("Message thread started.\n");
//
//	while (receivingRunning) {
//		int recvid = MsgReceivePulse(channelID, &msg, sizeof(_pulse), nullptr);
//
//		if (recvid < 0) {
//			perror("MsgReceivePulse failed!");
//			exit(EXIT_FAILURE);
//		}
//
//		if (recvid == 0) {	//pulse received.
//
//			//Stop thread while it blocks.
//			if (msg.code == PULSE_STOP_THREAD) {
//				printf("Thread kill code received!\n");
//				receivingRunning = false;
//			}
//
//			if (msg.code == PULSE_INTR_ON_PORT0){
//				handleInterrupt();
//			}
//
//			// Do not ignore OS pulses!
//		}
//	}
//
//	printf("Message thread stops...\n");
//}



//typedef struct interuptet_pin {
//	int pin;
//	int current_level;
//} interuptet_pin;

//void handleInterrupt(void) {
//	uintptr_t gpioBase = mmap_device_io(GPIO_REGISTER_LENGHT, GPIO_PORT0);
//
//	unsigned int intrStatusReg = in32(uintptr_t(gpioBase + GPIO_IRQSTATUS_1));
//
//	out32(uintptr_t(gpioBase + GPIO_IRQSTATUS_1), 0xffffffff);	//clear all interrupts.
//	InterruptUnmask(INTR_GPIO_PORT0, interruptID);				//unmask interrupt.
//
//	for (int pin = 0; pin < 32; pin++) {
//		unsigned int mask = (uint32_t) BIT_MASK(pin);
//		if (intrStatusReg == mask) {
//			int current_level = (in32((uintptr_t) gpioBase + GPIO_DATAIN) >> pin) & 0x1;
//			printf("Interrupt on pin %d, now %d\n", pin, current_level);
//		}
//	}
//}


