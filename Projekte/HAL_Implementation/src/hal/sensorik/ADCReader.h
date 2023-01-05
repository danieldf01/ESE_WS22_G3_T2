/*
 * ADCReader.h
 *
 *  Created on: 01.11.2022
 *      Author: User
 */

#ifndef HAL_SENSORIK_ADCREADER_H_
#define HAL_SENSORIK_ADCREADER_H_

#include <stdint.h>
#include <sys/neutrino.h>
#include <errno.h>
#include <thread>
#include <stdlib.h>
#include <hw/inout.h>

#include "Hoehenauswertung.h"



#define ADC_IRQ_NUMBER 16

#define EVT_ADC_VALUE 0x0A

#define ADC_START_ADDRESS 0x44E0D000
#define ADC_ADDRESS_LENGTH 0x2000

#define ADC_IRQ_ENABLE_SET(base) (uintptr_t)base + 0x2c
#define ADC_IRQ_ENABLE_CLR(base) (uintptr_t)base + 0x30
#define ADC_IRQ_STATUS(base) (uintptr_t)base + 0x28
#define ADC_CTRL(base) (uintptr_t)base + 0x40
#define ADC_DATA(base) (uintptr_t)base + 0x100

#define GPIO1_ADDRESS_START (uint64_t)0x4804C000
#define GPIO1_ADDRESS_LENGTH 0x1000
#define GPIO_SET_REGISTER(base) (uintptr_t)base + 0x194
#define GPIO_CLEAR_REGISTER(base) (uintptr_t)base + 0x190

extern int errno;

class ADCReader {
public:
	ADCReader();
	virtual ~ADCReader();
	int runADCReader();
};

#endif /* HAL_SENSORIK_ADCREADER_H_ */
