/*
 * HALSensorikDemo.h
 *
 *  Created on: 01.11.2022
 *      Author: User
 */

#ifndef HAL_DEMO_HALSENSORIKDEMO_H_
#define HAL_DEMO_HALSENSORIKDEMO_H_

#include "../sensorik/SensorikSteuerung.h"

class HALSensorikDemo {
private:
	SensorikSteuerung *steuerung = nullptr;
public:
	HALSensorikDemo(OutputDispatcher &dispatcher, HALAktorik &aktorik);
	virtual ~HALSensorikDemo();
	void runDemo();
};

#endif /* HAL_DEMO_HALSENSORIKDEMO_H_ */
