/*
 * Fehlerzustand.cpp
 *
 *  Created on: 12.12.2022
 *      Author: acy003
 */

#include "Fehlerzustand.h"

void Fehlerzustand::handlePulse(int code, int value){

	switch(code){

	case CODE_FBM_1: //pulse von FBM1
		pulseFBM1(value);
		break;

	case CODE_FBM_2: //Pulse von FBM2
		pulseFBM2(value);
		break;

	case CODE_ZEIT_1:
		pulseZeit1(value);
		break;

	case CODE_ZEIT_2:
		pulseZeit2(value);
		break;

	}
}

/**
 *
 * PULSE VON FBM1
 *
 */
void Fehlerzustand::pulseFBM1(int value){
	switch (value) {
	case E_STOP_AN:
		eStop(1);
		break;

	case FEHLER_HOCH:
		fehlerCount++;
		break;

	case FEHLER_RUNTER:
		fehlerCount--;
		if (fehlerCount == 0) {
			MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,
					_PULSE_CODE_MINAVAIL, FEHLER_G_UNQUITTIERT);
			MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_G_UNQUITTIERT);
			MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1,
					STOP_RUNTER_1);
			MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2,
					STOP_RUNTER_2);
			new (this) FehlerGegangenUnquittiert;
		}
		break;

	case T_RESET_AUS:
		quittiert();
		break;

	case LS_RUTSCHE_AUS:	//active low+
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1,
				LS_RUTSCHE_AUS);
		break;

	case LS_RUTSCHE_AN: //active low+
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1,
				LS_RUTSCHE_AN);
		break;

	case SCHNELL_HOCH_1:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, SCHNELL_HOCH_1);
		break;

	case SCHNELL_RUNTER_1:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, SCHNELL_RUNTER_1);
		break;

	case LANGSAM_HOCH_1:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, LANGSAM_HOCH_1);
		break;

	case LANGSAM_RUNTER_1:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, LANGSAM_RUNTER_1);
		break;

	case STOP_HOCH_1:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, STOP_HOCH_1);
		break;

	case STOP_RUNTER_1:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1, STOP_RUNTER_1);
		break;

	case MOT_R_AN_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, MOTOR_AN);
		break;

	case MOT_R_AUS_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, MOTOR_AUS);
		break;

	case MOT_LANGSAM_AN_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, MOTOR_LANGSAM_AN);
		break;

	case MOT_LANGSAM_AUS_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, MOTOR_LANGSAM_AUS);
		break;

	case MOT_STOP_AN_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, MOTOR_STOP_AN);
		MsgSendPulse(auswertungID1, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, MOTOR_STOP_AN);
		break;

	case MOT_STOP_AUS_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL,MOTOR_STOP_AUS);
		MsgSendPulse(auswertungID1, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, MOTOR_STOP_AUS);
		break;

	case WARNUNG_AUS:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL,RUTSCHE_FREI);
		warnungsCount--;
		break;

	case WARNUNG_AN:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL,RUTSCHE_VOLL);
		warnungsCount++;
		break;

	case TIMER_RUTSCHE:
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1,TIMER_RUTSCHE);
		break;

	case HS_LEEREN:
		MsgSendPulse(auswertungID1, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, HS_LEEREN);
		break;
	}
}

/**
 *
 * PULSE VON FBM2
 *
 */
void Fehlerzustand::pulseFBM2(int value){
	switch(value){

	case E_STOP_AN:
		eStop(2);
		break;

	case T_RESET_AUS:
		quittiert();
		break;

	case FEHLER_RUNTER:
		fehlerCount--;
		if(fehlerCount==0){
			MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_G_UNQUITTIERT);
			MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_G_UNQUITTIERT);
			MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, STOP_RUNTER_1);
			MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, STOP_RUNTER_2);
			new (this) FehlerGegangenUnquittiert;
		}
		break;

	case LS_RUTSCHE_AUS:	//active low+
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,LS_RUTSCHE_AUS);
		break;

	case LS_RUTSCHE_AN: //active low+
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,LS_RUTSCHE_AN);
		break;

	case WARNUNG_AUS:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,RUTSCHE_FREI);
		warnungsCount--;
		break;

	case WARNUNG_AN:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,RUTSCHE_VOLL);
		warnungsCount++;
		break;

	case TIMER_RUTSCHE:
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,TIMER_RUTSCHE);
		break;
	}
}

/**
 *
 * PULSE VON zeitFBM2
 *
 */
void Fehlerzustand::pulseZeit1(int value){

}

/**
 *
 * PULSE VON zeitFBM2
 *
 */
void Fehlerzustand::pulseZeit2(int value){

}


void Fehlerzustand::updateAuswertung(){

}


void Fehlerzustand::eStop(int estop){
	cout << "switched to EStop1"<< endl;
	MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, BETRIEBSMODUS_AUS );
	MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, E_STOP_AN );
	MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, E_STOP_AN);
	MsgSendPulse(fsmLSA1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(auswertungID1, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, HS_LEEREN);
	MsgSendPulse(auswertungID2, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, HS_LEEREN);
	MsgSendPulse(auswertungID1, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_STOP_AN);
	MsgSendPulse(auswertungID2, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_STOP_AN);
	MsgSendPulse(fsmLSAbisHS1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmWsErkennung1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmHSbisSep1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmSepBisRut1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmSepBisLSEnde_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmLSA2_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, E_STOP_AN);
	zeitFBM1->clearLists();
	zeitFBM2->clearLists();
	MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,ESTOP_AN);
	fehlerCount=0;
	warnungsCount=0;
	if(estop==1){
		eStop1=true;
		}
		else{
		eStop2=true;
		}
	new (this) EStop;
}

void Fehlerzustand::quittiert(){
	//TODO Quittiert an alle FSMs schicken
	MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_QUITTIERT);
	MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_QUITTIERT);
	cout << "fehler quittiert" << endl;
	new (this) FehlerQuittiert;
	MsgSendPulse(fsmLSA1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, QUITTIERT);
	MsgSendPulse(fsmLSAbisHS1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, QUITTIERT);
	MsgSendPulse(fsmWsErkennung1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, QUITTIERT);
	MsgSendPulse(fsmHSbisSep1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, QUITTIERT);
	MsgSendPulse(fsmSepBisRut1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, QUITTIERT);
	MsgSendPulse(fsmSepBisLSEnde_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, QUITTIERT);
	MsgSendPulse(fsmLSA2_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, QUITTIERT);
}
