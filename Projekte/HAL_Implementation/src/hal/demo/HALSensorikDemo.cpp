/*
 * HALSensorikDemo.cpp
 *
 *  Created on: 01.11.2022
 *      Author: User
 */

#include "HALSensorikDemo.h"

HALSensorikDemo::HALSensorikDemo() {
	// TODO Auto-generated constructor stub
	this->gpio = new GPIO();
	this->adcReader = new ADCReader();
}

HALSensorikDemo::~HALSensorikDemo() {
	// TODO Auto-generated destructor stub
}

void HALSensorikDemo::runDemo() {
	//gpio->runGPIO();
	adcReader->runADCReader();
}
