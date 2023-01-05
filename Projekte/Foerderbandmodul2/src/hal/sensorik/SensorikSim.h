/*
 * SensorikSim.h
 *
 *  Created on: Dec 8, 2022
 *      Author: bardia
 */

#ifndef HAL_SENSORIK_SENSORIKSIM_H_
#define HAL_SENSORIK_SENSORIKSIM_H_

#include <stdio.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/procmgr.h>
#include <iostream>
#include <thread>
#include <chrono>

#include "ADC_Sources/ADC.h"
#include "ADC_Sources/TSCADC.h"
#include "../../dispatcher/OutputDispatcher.h"
#include "../demo/HALAktorik.h"
//
#include "simqnxgpioapi.h"
#include "simqnxirqapi.h"


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
#define WINDOW_SIZE 125

/* My pulse codes */
#define PULSE_STOP_THREAD _PULSE_CODE_MINAVAIL + 1
#define PULSE_INTR_ON_PORT0 _PULSE_CODE_MINAVAIL + 2
#define PULSE_ADC_SAMLING_DONE _PULSE_CODE_MINAVAIL + 3

class SensorikSim {
public:
	bool receivingRunning = false;
	int interruptID;
	SensorikSim(OutputDispatcher &dispatcher, HALAktorik &halaktorik);
	virtual ~SensorikSim();
	void receivingRoutine(int, ADC *adc);
	void handleInterrupt();
	int runHALSteuerung();
	void handleADCInterrupt(_pulse *msg);
	int window(const int messung);
	TSCADC *tsc;
		ADC *adc;

	OutputDispatcher *outputDispatcher = nullptr;
		HALAktorik *aktorik= nullptr;
	// For the ADC output
		int count;
		int adcSum;
		int adcAverage;
};

#endif /* HAL_SENSORIK_SENSORIKSIM_H_ */
