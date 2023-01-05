/*
 * BaseStateMotorsteuerung1.h
 *
 *  Created on: 12.12.2022
 *      Author: acy003
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_MOTORSTEUERUNG_MOTOR_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_MOTORSTEUERUNG_MOTOR_H_


#include "../../../Defines.h"
#include "../../../../dispatcher/QnetHandler.h"
#include "../../../Zeit/Zeitmanager.h"

class Motor {
public:

	int cnt_langsam;
	int cnt_stop;
	int cnt_schnell;

	int logikID;
	Zeitmanager *zeitFBM1;
	Zeitmanager *zeitFBM2;

	Motor(Zeitmanager *zeitmanager1, Zeitmanager *zeitmanager2);
	virtual ~Motor();
	 void handlePulse(int code,int value);
};



#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_MOTORSTEUERUNG_MOTOR_H_ */
