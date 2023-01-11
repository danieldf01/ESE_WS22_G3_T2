/*
 * OutputDispatcher.cpp
 *
 *  Created on: Nov 13, 2022
 *      Author: Bardia
 */
#include "OutputDispatcher.h"

//global variables
//QnetHandler?
//Logik logik
using namespace std;

OutputDispatcher::OutputDispatcher(){
	this->qnetHandler = QnetHandler();
	logikID=0;
	inputID=0;
	//TODO mit Kommunikation verbinden
}

OutputDispatcher::~OutputDispatcher(){
	qnetHandler.~QnetHandler();
}

void OutputDispatcher::init(){
	logikID = qnetHandler.connectServer(LOGIK);
	inputID = qnetHandler.connectServer(INPUTDISPATCHER);
}

void OutputDispatcher::dispatchADC(int wert, int anlage){
	if(anlage == 1){
		//cout << "adc wert erhalten: " << wert << endl;
		MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_ADC_1, wert);
	} else if(anlage == 2){
//		cout << "OutputDispatcher adc wert von Anlage 2 erhalten: " << wert << endl;
		MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_ADC_2, wert);
	}
}

void OutputDispatcher::dispatchOutput(int pin, int currentlevel){
	switch (pin) {
	case  E_STOP_PIN:
		if(currentlevel == 0){
			MsgSendPulse(inputID, sched_get_priority_max(SCHED_FIFO), _PULSE_CODE_MINAVAIL, ESTOP_AN);
			MsgSendPulse(logikID, sched_get_priority_max(SCHED_FIFO), CODE_FBM_1, E_STOP_AN);
			////cout << "estopp an" << endl;
		} else {
			MsgSendPulse(inputID, sched_get_priority_max(SCHED_FIFO), _PULSE_CODE_MINAVAIL, ESTOP_AUS);
			MsgSendPulse(logikID, sched_get_priority_max(SCHED_FIFO), CODE_FBM_1, E_STOP_AUS);
			////cout << "estopp aus" << endl;
		}
		break;

	case WEICHE1:
		//this_thread::sleep_for(chrono::milliseconds(50));
		MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT , CODE_FBM_1, WEICHE1);
		break;
	case AUSWERFER1:
		//this_thread::sleep_for(chrono::milliseconds(50));
		MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT , CODE_FBM_1, AUSWERFER1);
		break;
	case WEICHE2:
		MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT , CODE_FBM_1, WEICHE2);
		break;
	case AUSWERFER2:
		MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT , CODE_FBM_1, AUSWERFER2);
		break;
	case WATCHDOG_ESTOP:
		MsgSendPulse(inputID, sched_get_priority_max(SCHED_FIFO), _PULSE_CODE_MINAVAIL, WATCHDOG_ESTOP);
		MsgSendPulse(logikID, sched_get_priority_max(SCHED_FIFO), CODE_FBM_1, WATCHDOG_ESTOP);
		break;

	case T_STOP_PIN:
		if(currentlevel==0){
			//Stop Taster gedrueckt
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, T_STOP_AN);
			//cout << "stop gedrueckt" << endl;
		} else{
			//Stop Taster losgelassen
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, T_STOP_AUS);
			//cout << "stop losgelassen" << endl;
		}
		break;

	case LS_ENDE_PIN:
		if(currentlevel==0){
			//LS_ENDE unterbrochen
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, LS_ENDE_AN);
			//cout << "LS_ENDE unterbrochen" << endl;
		} else{
			//LS_ENDE freigegeben
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, LS_ENDE_AUS);
			//cout << "LS_ENDE freigegeben" << endl;
		}
		break;

	case LS_SEPERATOR_PIN:
		if(currentlevel==0){
			//LS_SEPERATOR unterbrochen
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, LS_SEPERATOR_AN);
			//cout << "LS_SEPERATOR unterbrochen" << endl;
		} else{
			//LS_SEPERATOR freigegeben
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, LS_SEPERATOR_AUS);
			//cout << "LS_SEPERATOR freigegeben" << endl;
		}
		break;

	case LS_ANFANG_PIN:
		if(currentlevel==0){
			//LS_ANFANG unterbrochen
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, LS_ANFANG_AN);
			cout << "LS_ANFANG unterbrochen" << endl;
		} else{
			//LS_ANFANG freigegeben
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, LS_ANFANG_AUS);
			cout << "LS_ANFANG freigegeben" << endl;
		}
		break;

	case HS_HOCH_OK_PIN:
		if(currentlevel==0){
			//HOCh_OK freigegeben
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, HS_HOCH_OK_AUS);
			//cout << "HOCH_OK unterbrochen" << endl;
		} else{
			//HOCK_OK unterbrochen
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, HS_HOCH_OK_AN);
			//cout << "HOCH_OK freigegeben" << endl;
		}
		break;

	case METALLSENSOR_PIN:
		if(currentlevel==0){
			//Metallsensor "freigegeben"
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, METALLSENSOR_AUS);
			//cout << "Metallsensor freigegeben" << endl;
		} else{
			//Metall erkannt
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, METALLSENSOR_AN);
			//cout << "Metall erkannt" << endl;
		}
		break;

	case LS_RUTSCHE_PIN:
		if(currentlevel==0){
			//LS_RUTSCHE unterbrochen
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, LS_RUTSCHE_AN);
			//cout << "LS_RUTSCHE unterbrochen" << endl;
		} else{
			//LS_RUTSCHE freigegeben
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, LS_RUTSCHE_AUS);
			//cout << "LS_RUTSCHE freigegeben" << endl;
		}
		break;

	case T_START_PIN:
		if(currentlevel==0){
			//Start Taster losgelassen
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, T_START_AUS);
			//cout << "START_TASTER losgelassen" << endl;
		} else{
			//Start Taster gedrueckt
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, T_START_AN);
			//cout << "START_TASTER gedrueckt" << endl;
		}
		break;

	case T_RESET_PIN:
		if(currentlevel==0){
			//Reset Taster losgelassen
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, T_RESET_AUS);
			//cout << "RESET losgelassen" << endl;
		} else{
			//Reset Taster gedrueckt
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, T_RESET_AN);
			//cout << "RESET gedrueckt" << endl;
		}
		break;

	case E_STOP_PIN_2:
		if(currentlevel == 0){
			MsgSendPulse(logikID, sched_get_priority_max(SCHED_FIFO), CODE_FBM_2, E_STOP_AN);
			MsgSendPulse(inputID, sched_get_priority_max(SCHED_FIFO), _PULSE_CODE_MINAVAIL, ESTOP_AN_2);
			//TODO E-Stopp An Signal weiterleiten
			cout << "OutputDispatcher estopp2 an" << endl;
		} else{
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, E_STOP_AUS);
			MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, ESTOP_AUS_2);
			cout << "OutputDispatcher estopp2 aus" << endl;
			//TODO E-Stopp Aus Signal weiterleiten
		}
		break;

	case T_STOP_PIN_2:
		if(currentlevel==0){
			//Stop Taster gedrueckt
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2, T_STOP_AN);
		} else{
			//Stop Taster losgelassen
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2, T_STOP_AUS);
		}
		break;

	case LS_ENDE_PIN_2:
		if(currentlevel==0){
			//LS_ENDE unterbrochen
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2, LS_ENDE_AN);
		} else{
			//LS_ENDE freigegeben
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2, LS_ENDE_AUS);
		}
		break;

	case LS_SEPERATOR_PIN_2:
		if(currentlevel==0){
			//LS_SEPERATOR unterbrochen
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2, LS_SEPERATOR_AN);
		} else{
			//LS_SEPERATOR freigegeben
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2, LS_SEPERATOR_AUS);
		}
		break;

	case LS_ANFANG_PIN_2:
		if(currentlevel==0){
			//LS_ANFANG unterbrochen
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2, LS_ANFANG_AN);
		} else{
			//LS_ANFANG freigegeben
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2, LS_ANFANG_AUS);
		}
		break;

	case HS_HOCH_OK_PIN_2:
		if(currentlevel==0){
			//HOCh_OK freigegeben
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2, HS_HOCH_OK_AUS);
		} else{
			//HOCK_OK unterbrochen
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2, HS_HOCH_OK_AN);
		}
		break;

	case METALLSENSOR_PIN_2:
		if(currentlevel==0){
			//Metallsensor "freigegeben"
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2, METALLSENSOR_AUS);
		} else{
			//Metall erkannt
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2, METALLSENSOR_AN);
		}
		break;

	case LS_RUTSCHE_PIN_2:
		if(currentlevel==0){
			//LS_RUTSCHE unterbrochen
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2, LS_RUTSCHE_AN);
		} else{
			//LS_RUTSCHE freigegeben
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2, LS_RUTSCHE_AUS);
		}
		break;

	case T_START_PIN_2:
		if(currentlevel==0){
			//Start Taster losgelassen
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2, T_START_AUS);
		} else{
			//Start Taster gedrueckt
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2, T_START_AN);
		}
		break;

	case T_RESET_PIN_2:
		if(currentlevel==0){
			//Reset Taster losgelassen
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2, T_RESET_AUS);
		}
		else{
			//Reset Taster gedrueckt
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2, T_RESET_AN);
		}
		break;
	}
}
