/*
 * Lichtschranke.cpp
 *
 *  Created on: 26.10.2022
 *      Author: acm496
 */
#include "GPIO.h"

/* Variables */
static bool receivingRunning;
static int interruptID;

/* Prototypes*/
static void receivingRoutine(int);	//TODO: Es ist jetzt static
static void handleInterrupt(void);	//TODO: Es ist jetzt static

using namespace std;

GPIO::GPIO() {

}

GPIO::~GPIO() {

}


int GPIO::runGPIO(){

	/* ### Setup ### */
	ThreadCtl(_NTO_TCTL_IO, 0);	//Request IO privileges for process.

	// Request interrupt and IO abilities.
	int procmgr_status = procmgr_ability(0,
	PROCMGR_ADN_ROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_INTERRUPT,
	PROCMGR_ADN_NONROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_INTERRUPT,
	PROCMGR_ADN_ROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_IO,
	PROCMGR_ADN_NONROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_IO,
	PROCMGR_AID_EOL);
	if (procmgr_status != EOK) {
		perror("Requested abilities failed or denied!");
		exit(EXIT_FAILURE);
	}

	InterruptEnable();			//Enables interrupts.

	//out32((uintptr_t) port1BaseAddr + GPIO_SETDATAOUT, BIT_MASK(SORTIERER_PIN));

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
	SIGEV_PULSE_INIT(&intr_event, conID, SIGEV_PULSE_PRIO_INHERIT,
			PULSE_INTR_ON_PORT0, 0);
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
	BIT_MASK(LS_ANFANG_PIN) | BIT_MASK(HS_HOCH_OK_PIN)
			| BIT_MASK(LS_SEPERATOR_PIN) | BIT_MASK(METALLSENSOR_PIN)
			| BIT_MASK(LS_ZUSTAND_SEPERATOR_PIN) | BIT_MASK(LS_RUTSCHE_PIN)
			| BIT_MASK(LS_ENDE_PIN) | BIT_MASK(T_START_PIN)
			| BIT_MASK(T_STOP_PIN) | BIT_MASK(T_RESET_PIN)
			| BIT_MASK(E_STOP_PIN)); //Add desired pins.
	out32((uintptr_t) port0BaseAddr + GPIO_IRQSTATUS_SET_1, temp);

	//	(for rising edge detection)
	temp = in32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT));//Read current config.
	temp |= (
	BIT_MASK(LS_ANFANG_PIN) | BIT_MASK(HS_HOCH_OK_PIN)
			| BIT_MASK(LS_SEPERATOR_PIN) | BIT_MASK(METALLSENSOR_PIN)
			| BIT_MASK(LS_ZUSTAND_SEPERATOR_PIN) | BIT_MASK(LS_RUTSCHE_PIN)
			| BIT_MASK(LS_ENDE_PIN) | BIT_MASK(T_START_PIN)
			| BIT_MASK(T_STOP_PIN) | BIT_MASK(T_RESET_PIN)
			| BIT_MASK(E_STOP_PIN));			//Add desired pins.

	out32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT), temp);//Write new config back.

	// 	(for falling edge detection)
	temp = in32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT));//Read current config.
	temp |= (
	BIT_MASK(LS_ANFANG_PIN) | BIT_MASK(HS_HOCH_OK_PIN)
			| BIT_MASK(LS_SEPERATOR_PIN) | BIT_MASK(METALLSENSOR_PIN)
			| BIT_MASK(LS_ZUSTAND_SEPERATOR_PIN) | BIT_MASK(LS_RUTSCHE_PIN)
			| BIT_MASK(LS_ENDE_PIN) | BIT_MASK(T_START_PIN)
			| BIT_MASK(T_STOP_PIN) | BIT_MASK(T_RESET_PIN)
			| BIT_MASK(E_STOP_PIN));			//Add desired pins.
	out32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT), temp);//Write new config back.

	/* ### Start thread for handling interrupt messages. */
	thread receivingThread = thread(&receivingRoutine, chanID);

	/* ### Waiting for demo. ### */
	if (DEMO) {
		printf("Demo time for %d minutes...\n", DEMO_DURATION);
		this_thread::sleep_for(chrono::minutes(DEMO_DURATION));	//main thread sleep.
		printf("Stopping in...\n");
		printf("3\n");
		this_thread::sleep_for(chrono::seconds(1));
		printf("2\n");
		this_thread::sleep_for(chrono::seconds(1));
		printf("1\n");
		this_thread::sleep_for(chrono::seconds(1));
		printf("NOW!\n");
	} else {
		while (true) {
			this_thread::sleep_for(chrono::hours(999999));
		}
	}

	/* ### Cleaning up. */

	// Detach interrupts.
	int intr_detach_status = InterruptDetach(interruptID);
	if (intr_detach_status != EOK) {
		perror("Detaching interrupt failed!");
		exit(EXIT_FAILURE);
	}

	// Stop receiving thread.
	MsgSendPulse(conID, -1, PULSE_STOP_THREAD, 0); //using prio of calling thread.
	receivingThread.join();

	// Reset registers.
	// ONLY IF YOUR THE ONLY PROGRAM WITH INTERRUPTS RUNNING ON THIS MACHINE!

	// Close channel
	int detach_status = ConnectDetach(conID);
	if (detach_status != EOK) {
		perror("Detaching channel failed!");
		exit(EXIT_FAILURE);
	}

	int destroy_status = ChannelDestroy(chanID);
	if (destroy_status != EOK) {
		perror("Destroying channel failed!");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}

void receivingRoutine(int channelID) {

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

			// Do not ignore OS pulses!
		}
	}

	printf("Message thread stops...\n");
}

typedef struct interuptet_pin {
	int pin;
	int current_level;
} interuptet_pin;

void handleInterrupt(void) {
	uintptr_t gpioBase = mmap_device_io(GPIO_REGISTER_LENGHT, GPIO_PORT0);

	unsigned int intrStatusReg = in32(uintptr_t(gpioBase + GPIO_IRQSTATUS_1));

	out32(uintptr_t(gpioBase + GPIO_IRQSTATUS_1), 0xffffffff);	//clear all interrupts.
	InterruptUnmask(INTR_GPIO_PORT0, interruptID);				//unmask interrupt.

	for (int pin = 0; pin < 32; pin++) {
		unsigned int mask = (uint32_t) BIT_MASK(pin);
		if (intrStatusReg == mask) {
			int current_level = (in32((uintptr_t) gpioBase + GPIO_DATAIN) >> pin) & 0x1;
			printf("Interrupt on pin %d, now %d\n", pin, current_level);

			// 1. E-Stopp info an Klasse uebergeben
			// 2. pin, current verschicken
			// LS_ANFANG_AN - > pin, current_level (AN/AUS) -> dispatchOutput(pin, currentlvl)
			// -> Switch(pin) (0-32 Pins fuer GPIO)
			// -> LS_ANFANG sei jetzt 10 -> Idee: KomponentenBits = bitMusterVonPin (Direkt bits fuer LS_ANFANG setzen)
			// -> current_level bearbeiten (low=0 oder high=4) -> Setzte LSB oder MSB auf 0 oder 1
			// -> Verbinde die Informationen bspw. mit AND, &
			// -> Verschicke die Nachricht per Qnet pulls Messages code: 0-127 (8bit-1bit) value 32bit
			// -> Beispielformat: code<AnlageID, KomponentenID>, value(WertInBitsVonDerKomponente)
			// -> Beispiel zum Format: code= 1000 1010, value = ...0000 0000 0001 (oder ...0000 0000 fuer low bei GPIO)
		}
	}
}




