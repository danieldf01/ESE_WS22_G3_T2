/*
 * HALSteuerung.h
 *
 *  Created on: 15.11.2022
 *      Author: User
 */

#ifndef SENSORIK_HALSTEUERUNG_H_
#define SENSORIK_HALSTEUERUNG_H_

#include <stdio.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/procmgr.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <sys/mman.h>
#include <hw/inout.h>

#include "QnetHandler.h"
#include "GPIOSetup.h"

//#include "simqnxgpioapi.h"
//#include "simqnxirqapi.h"

/*Include ADC Sources*/
#include "ADC_Sources/ADC.h"
#include "ADC_Sources/TSCADC.h"

/* Interrupt numbers  (spruh73l.pdf S.465 ff.) */
#define INTR_GPIO_PORT0 97
#define INTR_GPIO_PORT1 99
#define INTR_GPIO_PORT2 33

/* GPIO port addresses (spruh73l.pdf S.177 ff.) */
#define GPIO_PORT0 0x44E07000
#define GPIO_PORT1 0x4804C000
#define GPIO_PORT2 0x481AC000
#define ADC_BASE 0x44E0D000 // Port for ADC

/* GPIO port registers length */
#define GPIO_REGISTER_LENGHT 0x1000
#define ADC_LENGTH 0x2000 // Length for ADC

#define GPIO_DATAIN 0x138
#define GPIO_SETDATAOUT 0x194
#define GPIO_CLEARDATAOUT 0x190

/* TSC_ADC register offsets (spruh73l.pdf S.1747) */
#define ADC_IRQ_ENABLE_SET 0x2c
#define ADC_IRQ_ENABLE_CLR 0x30
#define ADC_IRQ_STATUS 0x28
#define ADC_CTRL 0x40
#define ADC_DATA 0x100

/* ADC irq pin mask */
#define ADC_IRQ_PIN_MASK 0x2

/* Actuators pin mapping */
#define MOTOR_RIGHT_PIN 12
#define SORTIERER_PIN 19
#define MOTOR_SLOW_PIN 14
#define MOTOR_STOP_PIN 15

/* My pulse codes */
#define PULSE_STOP_THREAD _PULSE_CODE_MINAVAIL + 1
#define PULSE_INTR_ON_PORT0 _PULSE_CODE_MINAVAIL + 2
#define PULSE_ADC_SAMLING_DONE _PULSE_CODE_MINAVAIL + 2

/* Helper macros */
#define BIT_MASK(x) (0x1 << (x))

/* Implementation */
using namespace std;

class HALSteuerung {
private:
	/* Variables */
	bool receivingRunning = false;
	int interruptID;
	QnetHandler *connector = nullptr;
	GPIOSetup *gpioSetup = nullptr;
	int conID;
public:
	HALSteuerung();
	virtual ~HALSteuerung();
	/* Function declaration */
	void runHALSteuerung();
	ADC* attachInterrupts();
	void detachInterrupts(ADC *adc);
	void receivingRoutine(int channelID, ADC *adc);
	void handleInterrupt(void);
};

#endif /* SENSORIK_HALSTEUERUNG_H_ */
