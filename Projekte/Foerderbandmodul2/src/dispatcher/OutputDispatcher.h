/*
 * OutputDispatcher.h
 *
 *  Created on: Nov 13, 2022
 *      Author: Bardia
 */

#include "QnetHandler.h"
#include <iostream>
#include <sched.h>

#ifndef OUTPUTDISPATCHER_H_
#define OUTPUTDISPATCHER_H_

#define INPUTDISPATCHER "server_inputdispatcher_2"
#define SERVER_KOM_SLAVE "KommunikationSlave"
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




class OutputDispatcher {
private:
	int inputID;
	int kommID;
	QnetHandler qnetHandler;
public:
	OutputDispatcher();
	virtual ~OutputDispatcher();
	void dispatchOutput(int,int);
	void dispatchADC(int);
	void init();
};



#endif /* OUTPUTDISPATCHER_H_ */
