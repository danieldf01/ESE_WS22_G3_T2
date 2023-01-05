/*
 * HALSensorikDemo.h
 *
 *  Created on: 01.11.2022
 *      Author: User
 */

#ifndef HAL_DEMO_HALSENSORIKDEMO_H_
#define HAL_DEMO_HALSENSORIKDEMO_H_

#include "../sensorik/HALSteuerung.h"

class HALSensorikDemo {
private:
	HALSteuerung *steuerung = nullptr;
public:
	HALSensorikDemo();
	virtual ~HALSensorikDemo();
	void runDemo();
};

#endif /* HAL_DEMO_HALSENSORIKDEMO_H_ */
