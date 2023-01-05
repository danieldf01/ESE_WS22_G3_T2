/*
 * GPIOSetup.h
 *
 *  Created on: 15.11.2022
 *      Author: User
 */

#ifndef SENSORIK_GPIOSETUP_H_
#define SENSORIK_GPIOSETUP_H_

#include <stdio.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/procmgr.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <sys/mman.h>
#include <hw/inout.h>

/* GPIO register offsets (spruh73l.pdf S.4877) */
#define GPIO_LEVELDETECT0 0x140
#define GPIO_LEVELDETECT1 0x144
#define GPIO_RISINGDETECT 0x148
#define GPIO_FALLINGDETECT 0x14C

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

#define GPIO_IRQSTATUS_0 0x2C
#define GPIO_IRQSTATUS_1 0x30
#define GPIO_IRQSTATUS_SET_0 0x34
#define GPIO_IRQSTATUS_SET_1 0x38

/* Helper macros */
#define BIT_MASK(x) (0x1 << (x))

class GPIOSetup {
public:
	GPIOSetup();
	virtual ~GPIOSetup();
	void requestGPIOAbiltiys();
	void configGPIOIRQEventTypes(uintptr_t port0BaseAddr);
};

#endif /* SENSORIK_GPIOSETUP_H_ */
