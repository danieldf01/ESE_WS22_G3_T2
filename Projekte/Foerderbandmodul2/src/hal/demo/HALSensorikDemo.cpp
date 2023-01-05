/*
 * HALSensorikDemo.cpp
 *
 *  Created on: 01.11.2022
 *      Author: User
 */

#include "HALSensorikDemo.h"

HALSensorikDemo::HALSensorikDemo(OutputDispatcher &dispatcher, HALAktorik &aktorik) {
	this->steuerung = new SensorikSteuerung(dispatcher,aktorik);
}

HALSensorikDemo::~HALSensorikDemo() {
	// TODO Auto-generated destructor stub
	steuerung->~SensorikSteuerung();
}

void HALSensorikDemo::runDemo() {
	steuerung->runHALSteuerung();
}
