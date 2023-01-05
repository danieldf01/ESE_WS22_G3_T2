/*
 * SenosrikSteuerung.h
 *
 *  Created on: 15.11.2022
 *      Author: Tobias Thoelen
 */

#ifndef SENSORIK_SENSORIKSTEUERUNG_H_
#define SENSORIK_SENSORIKSTEUERUNG_H_


#include "GPIOSetup.h"

/*Include ADC Sources*/
#include "ADC_Sources/ADC.h"
#include "ADC_Sources/TSCADC.h"
#include "../../dispatcher/OutputDispatcher.h"
#include "SensorikQnet.h"
#include "../demo/HALAktorik.h"


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
#define PULSE_ADC_SAMLING_DONE _PULSE_CODE_MINAVAIL + 3

/* Helper macros */
#define BIT_MASK(x) (0x1 << (x))
#define WINDOW_SIZE 125 //HW 125  SIM 1 ====================================================================

/* Implementation */
using namespace std;

class SensorikSteuerung {
private:
	/* Variables */
	bool receivingRunning = false;
	int interruptID;
	SensorikQnet *connector = nullptr;
	GPIOSetup *gpioSetup = nullptr;
	OutputDispatcher *outputDispatcher = nullptr;
	HALAktorik *aktorik= nullptr;

	TSCADC *tsc;
	ADC *adc;

	// For the ADC output
	int count;
	int adcSum;
	int adcAverage;

public:
	SensorikSteuerung(OutputDispatcher &dispatcher,HALAktorik &halaktorik);
	virtual ~SensorikSteuerung();
	/* Function declaration */
	void runHALSteuerung();
	ADC* attachInterrupts(int conID);
	void detachInterrupts(ADC *adc);
	void receivingRoutine(int channelID, ADC *adc);
	void handleInterrupt(void);
	void handleADCInterrupt(_pulse *msg);
	int window(const int messung);
};

#endif /* SENSORIK_SENSORIKSTEUERUNG_H_ */
