/*
 * FehlerGegangenUnquittiert.cpp
 *
 *  Created on: 12.12.2022
 *      Author: acy003
 */

#include "FehlerGegangenUnquittiert.h"

void FehlerGegangenUnquittiert::handlePulse(int code , int value){

	switch(code){

	case CODE_FBM_1: //pulse von GPIO_1

	switch(value){
	//FBM1 GPIO_Interrupt

	case E_STOP_AN:
		eStop(1);
		break;
	case FEHLER_HOCH:
		fehlerCount++;
		//MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,FEHLER_AN);
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL + 1, STOP_HOCH_1);
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,	_PULSE_CODE_MINAVAIL + 2, STOP_HOCH_2);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,FEHLER_AN);
		new (this) Fehlerzustand;
		break;

	case T_RESET_AUS:
		//MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,FEHLER_AUS);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,FEHLER_AUS);
		//MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,BETRIEBSMODUS_AN);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,BETRIEBSMODUS_AN);
		new (this) Betriebszustand;
		break;
	case LS_ANFANG_AN: 		//active low+
		MsgSendPulse(fsmLSA1_ID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,LS_ANFANG_AN);
		break;
	case HS_HOCH_OK_AUS: //active high+

		break;
	case LS_SEPERATOR_AN: //active low+


		break;
	case METALLSENSOR_AUS: //active high+

		break;
	case LS_ZUSTAND_SEPERATOR_AUS: 	//active high+

		break;

	case LS_ENDE_AN:	//active low+

		break;
	case T_START_AUS:  		//active high+

		break;
	case T_STOP_AN: 	//active low+

		break;
	case LS_ANFANG_AUS:		//active low+
		MsgSendPulse(fsmLSA1_ID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, LS_ANFANG_AUS);
		break;
	case HS_HOCH_OK_AN:	//active high+

		break;
	case LS_SEPERATOR_AUS://active low+

		break;
	case METALLSENSOR_AN:	//active high+

		break;
	case LS_ZUSTAND_SEPERATOR_AN:	//active high+

		break;
	case LS_RUTSCHE_AUS:	//active low+
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,LS_RUTSCHE_AUS);
		break;
	case LS_RUTSCHE_AN: //active low+
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,LS_RUTSCHE_AN);
		break;
	case LS_ENDE_AUS:		//active low+

		break;
	case T_START_AN:		//active high+

		break;
	case T_STOP_AUS:

		break;
	case SCHNELL_HOCH_1:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,SCHNELL_HOCH_1);
		break;
	case SCHNELL_RUNTER_1:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,SCHNELL_RUNTER_1);
		break;
	case LANGSAM_HOCH_1:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,LANGSAM_HOCH_1);
		break;
	case LANGSAM_RUNTER_1:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,LANGSAM_RUNTER_1);
		break;
	case STOP_HOCH_1:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,STOP_HOCH_1);
		break;
	case STOP_RUNTER_1:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,STOP_RUNTER_1);
		break;
	case MOT_R_AN_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,MOTOR_AN);
		break;
	case MOT_R_AUS_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,MOTOR_AUS);
		break;
	case MOT_LANGSAM_AN_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,MOTOR_LANGSAM_AN);
		break;
	case MOT_LANGSAM_AUS_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,MOTOR_LANGSAM_AUS);
		break;
	case MOT_STOP_AN_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,MOTOR_STOP_AN);
		MsgSendPulse(auswertungID1,SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_STOP_AN);
		break;
	case MOT_STOP_AUS_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,MOTOR_STOP_AUS);
		MsgSendPulse(auswertungID1,SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_STOP_AUS);
		break;



		//Pulse von substates fuer fbm1
	case WARNUNG_AUS:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,RUTSCHE_FREI);
		warnungsCount--;
		break;
	case WARNUNG_AN:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,RUTSCHE_VOLL);
		warnungsCount++;
		break;
	case HS_AKTIV:
		if (MsgSendPulse(fsmLSAbisHS1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, HS_AKTIV) == -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;
	case WS_TYP:
		if (MsgSendPulse(fsmWsErkennung1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, WS_TYP) == -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		break;
	case WS_IN_LS_A_BIS_HS:
		if (MsgSendPulse(fsmLSAbisHS1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, WS_IN_LS_A_BIS_HS) == -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		zeitFBM1->startMessung(3000+zeitFBM1->getTime(), FEHLER_WS_VERSCHWUNDEN, wsListen->ws_list_LSAnfang_bis_HS.back().getiD());
		break;
	case WS_ERSTELLT:
		zeitFBM1->startMessung(2000 + zeitFBM1->getTime(), FEHLER_WS_STECKT_FEST_LSA, wsListen->ws_LSAnfang->getiD());
		break;
	case WS_IN_HS:
		if (MsgSendPulse(fsmWsErkennung1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, WS_IN_HS) == -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		zeitFBM1->startMessung(1300 + zeitFBM1->getTime(), FEHLER_HOEHENMESSUNG, wsListen->ws_Hoehensensor_1->getiD());
		break;
	case HS_LEEREN:
		MsgSendPulse(auswertungID1, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, HS_LEEREN);
		break;
	case TIMER_RUTSCHE:
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,TIMER_RUTSCHE);
		break;
	}
	break;

	case CODE_FBM_2: //Pulse von GPIO_2
	cout << "GPIO_2 Interrupt erhalten" <<value << endl;
	switch(value){

	case LS_ANFANG_AN: 		//active low+

		break;
	case HS_HOCH_OK_AUS: //active high+

		break;
	case LS_SEPERATOR_AN: //active low+

		break;
	case METALLSENSOR_AUS: //active high+

		break;
	case LS_ZUSTAND_SEPERATOR_AUS: 	//active high+

		break;
	case LS_ENDE_AN:	//active low+

		break;
	case T_START_AUS:  		//active high+

		break;
	case T_STOP_AN: 	//active low+

		break;
	case E_STOP_AN:
		eStop(2);
		break;
	case LS_ANFANG_AUS:		//active low+

		break;
	case HS_HOCH_OK_AN:	//active high+

		break;
	case LS_SEPERATOR_AUS://active low+

		break;
	case METALLSENSOR_AN:	//active high+

		break;
	case LS_ZUSTAND_SEPERATOR_AN:	//active high+

		break;
	case LS_RUTSCHE_AUS:	//active low+
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,LS_RUTSCHE_AUS);
		break;
	case LS_RUTSCHE_AN: //active low+
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,LS_RUTSCHE_AN);
		break;
	case LS_ENDE_AUS:		//active low+


		break;
	case T_START_AN:		//active high+

		break;
	case T_RESET_AUS:
		//MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,FEHLER_AUS);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,FEHLER_AUS);
		//MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,BETRIEBSMODUS_AN);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,BETRIEBSMODUS_AN);
		new (this) Betriebszustand;
		break;
	case SCHNELL_HOCH_2:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,SCHNELL_HOCH_2);
		break;
	case SCHNELL_RUNTER_2:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,SCHNELL_RUNTER_2);
		break;
	case LANGSAM_HOCH_2:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,LANGSAM_HOCH_2);
		break;
	case LANGSAM_RUNTER_2:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,LANGSAM_RUNTER_2);
		break;
	case STOP_HOCH_2:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,STOP_HOCH_2);
		break;
	case STOP_RUNTER_2:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,STOP_RUNTER_2);
		break;
	case MOT_LANGSAM_AN_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,MOTOR_LANGSAM_AN);
		break;
	case MOT_LANGSAM_AUS_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,MOTOR_LANGSAM_AUS);
		break;
	case MOT_R_AN_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,MOTOR_AN);
		break;
	case MOT_R_AUS_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,MOTOR_AUS);
		break;
	case MOT_STOP_AN_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,MOTOR_STOP_AN);
		MsgSendPulse(auswertungID2,SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_STOP_AN);
		break;
	case MOT_STOP_AUS_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,MOTOR_STOP_AUS);
		MsgSendPulse(auswertungID2,SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_STOP_AUS);
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
	case HS_AKTIV:
		//TODO Weiterleiten an FSM
		cout << "HS_AKTIV_1" <<endl;
		break;
	case WS_TYP:
		//TODO Weiterleiten an FSM

		break;
	case WS_IN_LS_A_BIS_HS:
		//TODO Weiterleiten an FSM

		break;
	case WS_IN_HS:
		//TODO Weiterleiten an FSM

		break;
	}
	break;
	case CODE_ADC_1:
		MsgSendPulse(auswertungID1, SIGEV_PULSE_PRIO_INHERIT, PULSE_ADC_SAMLING_WINDOW_DONE, value);
		break;

	case CODE_ADC_2:
		MsgSendPulse(auswertungID2, SIGEV_PULSE_PRIO_INHERIT,	PULSE_ADC_SAMLING_WINDOW_DONE, value);
		break;
	case CODE_ZEIT_1: //Pulse von zeitFBM1
		switch(value){
		case FEHLER_WS_STECKT_FEST_LSA:
			if (MsgSendPulse(fsmLSA1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_WS_STECKT_FEST_LSA) == -1) {
				perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
				exit(EXIT_FAILURE);
			}
			break;
		case FEHLER_WS_VERSCHWUNDEN:
			if (MsgSendPulse(fsmLSAbisHS1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_WS_VERSCHWUNDEN) == -1) {
				perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
				exit(EXIT_FAILURE);
			}
			break;
		case FEHLER_HOEHENMESSUNG:
			if (MsgSendPulse(fsmWsErkennung1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_HOEHENMESSUNG) == -1) {
				perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
				exit(EXIT_FAILURE);
			}
		}
		break;
		case CODE_ZEIT_2: //Pulse von zeitFBM2

			break;
	}
}

/**
 *
 * PULSE VON FBM1
 *
 */
void FehlerGegangenUnquittiert::pulseFBM1(int value){

}

/**
 *
 * PULSE VON FBM2
 *
 */
void FehlerGegangenUnquittiert::pulseFBM2(int value){

}

/**
 *
 * PULSE VON zeitFBM2
 *
 */
void FehlerGegangenUnquittiert::pulseZeit1(int value){

}

/**
 *
 * PULSE VON zeitFBM2
 *
 */
void FehlerGegangenUnquittiert::pulseZeit2(int value){

}

void FehlerGegangenUnquittiert::updateAuswertung(){

}

void FehlerGegangenUnquittiert::eStop(int estop){
	cout << "switched to EStop1"<< endl;
	MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,BETRIEBSMODUS_AUS );
	MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,E_STOP_AN );
	MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,E_STOP_AN);
	MsgSendPulse(fsmLSA1_ID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(auswertungID1, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, HS_LEEREN);
	MsgSendPulse(auswertungID2, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, HS_LEEREN);
	MsgSendPulse(auswertungID1, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, MOTOR_STOP_AN);
	MsgSendPulse(auswertungID2, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, MOTOR_STOP_AN);
	MsgSendPulse(fsmLSAbisHS1_ID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmWsErkennung1_ID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, E_STOP_AN);
	zeitFBM1->clearLists();
	zeitFBM2->clearLists();
	//MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,ESTOP_AN);
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
