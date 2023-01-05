/*
 * HALSensorikDemo.cpp
 *
 *  Created on: 01.11.2022
 *      Author: User
 */

#include "HALSensorikDemo.h"

HALSensorikDemo::HALSensorikDemo() {
	this->steuerung = new HALSteuerung();
}

HALSensorikDemo::~HALSensorikDemo() {
	// TODO Auto-generated destructor stub
}

void HALSensorikDemo::runDemo() {
	steuerung->runHALSteuerung();
}
