/*
 * Kommunikation.h
 *
 *  Created on: 25.11.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef KOMMUNIKATION_KOMMUNIKATION_H_
#define KOMMUNIKATION_KOMMUNIKATION_H_

#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <thread>
#include <sys/dispatch.h>
#include <mutex>

#include "Watchdog.h"
#include "../dispatcher/QnetHandler.h"
#include "../dispatcher/OutputDispatcher.h"

#define SERVER_KOM_SLAVE "KommunikationSlave"
#define SERVER_KOM_MASTER "KommunikationMaster"
#define SERVER_INDIS "server_inputdispatcher_2"

#define CODE_FBM_1		_PULSE_CODE_MINAVAIL + 1
#define CODE_FBM_2		_PULSE_CODE_MINAVAIL + 2
#define CODE_ADC_1		_PULSE_CODE_MINAVAIL + 3
#define CODE_ADC_2		_PULSE_CODE_MINAVAIL + 4

#define WATCHDOG_INIT			52
#define INIT_NOTIF				55
#define CHID_SENT				60
#define WATCHDOG_SEND_NOTIF 	666

#define LS_ANFANG_AN		2			//active low
#define HS_HOCH_OK_AUS		4    		//active high
#define LS_SEPERATOR_AN 	5    		//active low
#define METALLSENSOR_AUS 	7    		//active high
#define LS_ZUSTAND_SEPERATOR_AUS 14	//active high
#define LS_RUTSCHE_AN		15    		//active low
#define LS_ENDE_AN			20			//active low
#define T_START_AUS			22        	//active high
#define T_STOP_AN			23        	//active low
#define T_RESET_AUS			26        	//active high
#define E_STOP_AN			27        	//active low

#define LS_ANFANG_AUS		102        		//active low
#define HS_HOCH_OK_AN		104    			//active high
#define LS_SEPERATOR_AUS	105    			//active low
#define METALLSENSOR_AN	107    			//active high
#define LS_ZUSTAND_SEPERATOR_AN 114    	//active high
#define LS_RUTSCHE_AUS		115    			//active low
#define LS_ENDE_AUS		120        		//active low
#define T_START_AN		122        		//active high
#define T_STOP_AUS			123        		//active low
#define T_RESET_AN		126        		//active high
#define E_STOP_AUS			127        		//active low

#define ESTOPP_AN_2		100	//E-Stopp weiterleitung an InputDispatcher
#define ESTOPP_AUS_2	101

//Signale von FMB1

//Defines fuer den InputDispatcher
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
#define LED_START_AN 32
#define LED_START_AUS 33
#define LED_RESET_AN 34
#define LED_RESET_AUS 35

class Kommunikation {
private:
	Watchdog *watchdog;
	QnetHandler *qnetHandler;
	OutputDispatcher *outputDispatcher;
	name_attach_t *attach;
	int coid_kom_m;
	int coid_indis;
	int chid_master;

	//TODO funktioniert das so?
	std::mutex watchdogM;
	bool watchdogES;
public:
	Kommunikation(OutputDispatcher &oD);
	virtual ~Kommunikation();
	void init();
	void receiveSignal();
	void pulseFBM1(int);
	void pulseFBM2(int);
	void sendPulse(int, int, int, int);
};

#endif /* KOMMUNIKATION_KOMMUNIKATION_H_ */
