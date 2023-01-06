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
	inputID=0;
	//TODO mit verschiedenen Logik Qnetservern verbinden
	//TODO mit Kommunikation verbinden

}

OutputDispatcher::~OutputDispatcher(){
	qnetHandler.~QnetHandler();
	//TODO Destruktor
}

void OutputDispatcher::init(){
	inputID = qnetHandler.connectServer(INPUTDISPATCHER);
	kommID = qnetHandler.connectServer(SERVER_KOM_SLAVE);
	//cout << sched_get_priority_max(SCHED_FIFO) << endl;
}

void OutputDispatcher::dispatchADC(int wert){
	MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL+4,wert);
	//TODO schicke ADC Wert an Logik Komponente


}
void OutputDispatcher::dispatchOutput(int pin, int currentlevel){
	//TODO Switch case fuer pin verarbeitung
	switch (pin) {

	case  E_STOP_PIN:

		if(currentlevel == 0){
			MsgSendPulse(inputID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL,0 );
			MsgSendPulse(kommID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL+2,27 );
			//TODO E-Stopp An Signal weiterleiten
			////cout << "estopp an" << endl;
		}
		else{
			MsgSendPulse(inputID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL,1 );
			MsgSendPulse(kommID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL+2,127 );
			////cout << "estopp aus" << endl;
			//TODO E-Stopp Aus Signal weiterleiten
		}
		break;
	case T_STOP_PIN:
		if(currentlevel==0){

			MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL+2, 23 );
			////cout << "stop gedrueckt" << endl;
			//Stop Taster gedrueckt
		}
		else{
			MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL+2, 123 );
			////cout << "stop losgelassen" << endl;
			//TODO Stop Taster losgelassen
		}
		break;
	case LS_ENDE_PIN:
		if(currentlevel==0){
			MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL+2, 20 );
			////cout << "LS_ENDE unterbrochen" << endl;
			//TODO LS_ENDE unterbrochen
		}
		else{
			MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL+2, 120 );
			//cout << "LS_ENDE freigegeben" << endl;
			//TODO LS_ENDE freigegeben
		}
		break;
	case LS_SEPERATOR_PIN:
		if(currentlevel==0){
			MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL+2, 5 );
			//cout << "LS_SEPERATOR unterbrochen" << endl;
			//TODO LS_SEPERATOR unterbrochen
		}
		else{
			MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL+2, 105 );
			//cout << "LS_SEPERATOR freigegeben" << endl;
			//TODO LS_SEPERATOR freigegeben
		}
		break;
	case LS_ANFANG_PIN:
		if(currentlevel==0){
			MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL+2, 2 );
			//cout << "LS_ANFANG unterbrochen" << endl;
			//TODO LS_ANFANG unterbrochen
		}
		else{
			MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL+2, 102 );
			//cout << "LS_ANFANG freigegeben" << endl;
			//TODO LS_ANFANG freigegeben
		}
		break;
	case HS_HOCH_OK_PIN:
		if(currentlevel==0){
			MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL+2, 4 );
			//cout << "HOCH_OK unterbrochen" << endl;
			//TODO HOCh_OK freigegeben
		}
		else{
			MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL+2, 104 );
			//cout << "HOCH_OK freigegeben" << endl;
			//TODO HOCK_OK unterbrochen
		}
		break;
	case METALLSENSOR_PIN:
		if(currentlevel==0){
			MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL+2, 7 );
			//cout << "Metallsensor freigegeben" << endl;
			//Metallsensor "freigegeben"
		}
		else{
			MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL+2, 107 );
			//cout << "Metall erkannt" << endl;
			//TODO Metall erkannt
		}
		break;
	case LS_RUTSCHE_PIN:
		if(currentlevel==0){
			MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL+2, 15 );
			//cout << "LS_RUTSCHE unterbrochen" << endl;
			//TODO LS_RUTSCHE unterbrochen
		}
		else{
			MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL+2, 115 );
			//cout << "LS_RUTSCHE freigegeben" << endl;
			//TODO LS_RUTSCHE freigegeben
		}
		break;
	case T_START_PIN:
		if(currentlevel==0){
			MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL+2, 22 );
			//cout << "START_TASTER losgelassen" << endl;
			//TODO Start Taster losgelassen
		}
		else{
			MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL+2, 122 );
			//cout << "START_TASTER gedrueckt" << endl;
			//TODO Start Taster gedrueckt
		}
		break;
	case T_RESET_PIN:
		if(currentlevel==0){
			MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL+2, 26 );
			MsgSendPulse(inputID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL,26 );
			//cout << "RESET losgelassen" << endl;
			//TODO Reset Taster losgelassen
		}
		else{
			MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL+2, 126 );
			//cout << "RESET gedrueckt" << endl;
			//Reset Taster gedrueckt
		}
		break;

	}
}
