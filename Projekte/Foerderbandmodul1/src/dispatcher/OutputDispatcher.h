/*
 * OutputDispatcher.h
 *
 *  Created on: Nov 13, 2022
 *      Author: Bardia
 */

#include <iostream>
#include <sched.h>
#include "QnetHandler.h"
#include "../Logik/Defines.h"

#ifndef OUTPUTDISPATCHER_H_
#define OUTPUTDISPATCHER_H_

#define LOGIK "server_logik"
#define INPUTDISPATCHER "server_inputdispatcher"
/* Sensors pin mapping (Aufgabenbeschreibung o. Schaltplan) */
#define LS_ANFANG_PIN 2		//active low+
#define HS_HOCH_OK_PIN 4	//active high+
#define LS_SEPERATOR_PIN 5	//active low+
#define METALLSENSOR_PIN 7	//active high+
#define LS_ZUSTAND_SEPERATOR_PIN 14	//active high+
#define LS_RUTSCHE_PIN 15	//active low+
#define LS_ENDE_PIN 20		//active low+
#define T_START_PIN  22		//active high+
#define T_STOP_PIN 23		//active low+
#define T_RESET_PIN 26		//active high+
#define E_STOP_PIN 27		//active low+

//Sensor pins der zweiten Anlage (aus der Pulse message ausgelesen)
#define LS_ANFANG_PIN_2 102		//active low+
#define HS_HOCH_OK_PIN_2 104	//active high+
#define LS_SEPERATOR_PIN_2 105	//active low+
#define METALLSENSOR_PIN_2 107	//active high+
#define LS_ZUSTAND_SEPERATOR_PIN_2 114	//active high+
#define LS_RUTSCHE_PIN_2 115	//active low+
#define LS_ENDE_PIN_2 120		//active low+
#define T_START_PIN_2  122		//active high+
#define T_STOP_PIN_2 123		//active low+
#define T_RESET_PIN_2 126		//active high+
#define E_STOP_PIN_2 127		//active low+

#define WATCHDOG_ESTOP 51

class OutputDispatcher {
private:
	int inputID;
	int logikID;
	int kommID;
	QnetHandler qnetHandler;
public:
	OutputDispatcher();
	virtual ~OutputDispatcher();
	void dispatchOutput(int,int);
	void dispatchADC(int ,int);
	void init();
};



#endif /* OUTPUTDISPATCHER_H_ */
