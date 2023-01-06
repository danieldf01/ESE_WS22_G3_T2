/*
 * InputDispatcher.h
 *
 *  Created on: Nov 13, 2022
 *      Author: bardia
 */

#ifndef INPUTDISPATCHER_H_
#define INPUTDISPATCHER_H_


#include "../hal/demo/HALAktorik.h"
#include "QnetHandler.h"
#include <string.h>

#define SERVER_INDIS "server_inputdispatcher_2"
#define ESTOP_AUS	1
#define ESTOP_AN	0
#define FEHLER_AN	2
#define FEHLER_AUS	3
#define STOP_AN		4
#define STOP_AUS	5
#define MOTOR_AN	6
#define MOTOR_AUS	7
#define MOTOR_STOP_AN	8
#define MOTOR_STOP_AUS	9
#define MOTOR_LANGSAM_AN	10
#define MOTOR_LANGSAM_AUS	11
#define AUSSORTIEREN	12
#define DURCHLASSEN	13
#define RUTSCHE_VOLL 14
#define RUTSCHE_FREI 15
#define ESTOP_AN_2 100
#define ESTOP_AUS_2 101
#define BETRIEBSMODUS_AN 20
#define BETRIEBSMODUS_AUS 21
#define FEHLER_QUITTIERT 22
#define FEHLER_G_UNQUITTIERT 23
#define SERVICE_MODE_AN 24
#define SERVICE_MODE_AUS 25
#define SEP_AN 30
#define SEP_AUS 31

#define WATCHDOG_ESTOP	51

class InputDispatcher {

private:
	HALAktorik *hal=nullptr;
	name_attach_t *attach;
	QnetHandler qnetHandler;
	bool estop=false;

public:
	InputDispatcher(HALAktorik &hal);
	virtual ~InputDispatcher();
	void receiveSignal();
	void test();
	void test2();
	int init();
	void fehlerQuittiert();
};



#endif /* INPUTDISPATCHER_H_ */
