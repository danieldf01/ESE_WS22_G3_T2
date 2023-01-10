/*
 * FehlerQuittiert.cpp
 *
 *  Created on: 12.12.2022
 *      Author: acy003
 */

#include "FehlerQuittiert.h"

void FehlerQuittiert::handlePulse(int code, int value){

	switch(code){

	case CODE_FBM_1: //pulse von FBM1
		pulseFBM1(value);
		break;

	case CODE_FBM_2: //Pulse von GPIO_2
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
void FehlerQuittiert::pulseFBM1(int value){
	switch(value){

	case E_STOP_AN:
		eStop(1);
		break;

	case FEHLER_HOCH:
		fehlerCount++;
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_AN);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_AN);
		new (this) Fehlerzustand;
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,LED_RESET_AN );
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, LED_RESET_AN);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,LED_START_AUS );
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, LED_START_AUS);
		break;

	case FEHLER_RUNTER:
		fehlerCount--;
		cout << "fehler runter" << fehlerCount << endl;
		MsgSendPulse(fsmHSbisSep1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_RUNTER);
		MsgSendPulse(fsmHSbisSep2_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_RUNTER);
		break;

	case T_START_AUS:
		keinFehler();
		break;

	case LS_RUTSCHE_AUS:	//active low+
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,LS_RUTSCHE_AUS);
		MsgSendPulse(fsmWsNichtAussortierbar_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1,LS_RUTSCHE_AUS);
		break;

	case LS_RUTSCHE_AN: //active low+
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,LS_RUTSCHE_AN);
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
		MsgSendPulse(auswertungID1,SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_STOP_AN);
		break;

	case STOP_RUNTER_1:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,STOP_RUNTER_1);
		MsgSendPulse(auswertungID1,SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_STOP_AUS);
		break;

	case MOT_R_AN_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_AN);
		break;

	case MOT_R_AUS_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_AUS);
		break;

	case MOT_LANGSAM_AN_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_LANGSAM_AN);
		break;

	case MOT_LANGSAM_AUS_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_LANGSAM_AUS);
		break;

	case MOT_STOP_AN_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_STOP_AN);
		break;

	case MOT_STOP_AUS_1:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_STOP_AUS);
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
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,TIMER_RUTSCHE);
		break;

	case HS_LEEREN:
		MsgSendPulse(auswertungID1, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, HS_LEEREN);
		break;

	case WS_AUSSORTIEREN:
		if (MsgSendPulse(fsmSepBisRut1_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, WS_AUSSORTIEREN) == -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		// TODO Timer anpassen ggf.
		zeitFBM1->startMessung(3000 + zeitFBM1->getTime(), FEHLER_WS_VERSCHWUNDEN_SEP_BIS_RUT, wsListen->ws_list_aussortieren.back().getiD());
		break;
	case QUITTIERT:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,FEHLER_QUITTIERT);
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,FEHLER_QUITTIERT);
		break;
	}
}

/**
 *
 * PULSE VON FBM2
 *
 */
void FehlerQuittiert::pulseFBM2(int value){
	switch(value){

	case E_STOP_AN:
		eStop(2);
		break;

	case LS_RUTSCHE_AUS:	//active low+
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,LS_RUTSCHE_AUS);
		MsgSendPulse(fsmWsNichtAussortierbar_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2,LS_RUTSCHE_AUS);
		break;
	case LS_RUTSCHE_AN: //active low+
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,LS_RUTSCHE_AN);
		break;

	case FEHLER_HOCH:
		fehlerCount++;
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_AN);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_AN);
		new (this) Fehlerzustand;
		break;

	case FEHLER_RUNTER:
		fehlerCount--;
		break;

	case T_START_AUS:
		keinFehler();
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
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, RUTSCHE_FREI);
		warnungsCount--;
		break;

	case WARNUNG_AN:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, RUTSCHE_VOLL);
		warnungsCount++;
		break;

	case TIMER_RUTSCHE:
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,TIMER_RUTSCHE);
		break;

	case WS_AUSSORTIEREN:
		if (MsgSendPulse(fsmSepBisRut2_ID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, WS_AUSSORTIEREN) == -1) {
			perror("[LOGIK_Betriebszustand] MsgSendPulse failed");
			exit(EXIT_FAILURE);
		}
		// TODO Timer anpassen ggf.
		zeitFBM2->startMessung(3000 + zeitFBM2->getTime(), FEHLER_WS_VERSCHWUNDEN_SEP_BIS_RUT, wsListen->ws_aussortieren_2->getiD());
		break;
	}
}

/**
 *
 * PULSE VON zeitFBM2
 *
 */
void FehlerQuittiert::pulseZeit1(int value){

}

/**
 *
 * PULSE VON zeitFBM2
 *
 */
void FehlerQuittiert::pulseZeit2(int value){

}

void FehlerQuittiert::updateAuswertung(){

}

void FehlerQuittiert::eStop(int estop){
	MsgSendPulse(inputID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL,BETRIEBSMODUS_AUS );
	MsgSendPulse(motorID, sched_get_priority_max(SCHED_FIFO),CODE_FBM_1,E_STOP_AN );
	MsgSendPulse(motorID, sched_get_priority_max(SCHED_FIFO),CODE_FBM_2,E_STOP_AN);
	MsgSendPulse(fsmLSA1_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmLSA2_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(auswertungID1, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, HS_LEEREN);
	MsgSendPulse(auswertungID2, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, HS_LEEREN);
	MsgSendPulse(auswertungID1, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, MOTOR_STOP_AN);
	MsgSendPulse(auswertungID2, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, MOTOR_STOP_AN);
	MsgSendPulse(fsmLSAbisHS1_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmLSAbisHS2_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmWsErkennung1_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmWsErkennung2_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmWsNichtAussortierbar_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(rutschenID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmHSbisSep1_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmHSbisSep2_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmSepBisRut1_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmSepBisRut2_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmPassieren_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmSepBisLSEnde1_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmSepBisLSEnde2_ID, sched_get_priority_max(SCHED_FIFO),_PULSE_CODE_MINAVAIL, E_STOP_AN);

	zeitFBM1->clearLists();
	zeitFBM2->clearLists();

	fehlerCount=0;
	warnungsCount=0;

	wsListen->sortierReihenfolge.clear();
	wsListen->sortierReihenfolge2.clear();

	if(estop==1){
		MsgSendPulse(kommID, sched_get_priority_max(SCHED_FIFO), CODE_FBM_1, ESTOP_AN);
		eStop1=true;
	} else{
		eStop2=true;
	}

	new (this) EStop;
	cout << "switched to EStop " << estop << endl;
}
void FehlerQuittiert::keinFehler(){
	if(fehlerCount==0){
		//TODO Quittiert an alle FSMs schicken
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_AUS);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_AUS);
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, BETRIEBSMODUS_AN);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, BETRIEBSMODUS_AN);
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, STOP_RUNTER_1);
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, STOP_RUNTER_2);
		MsgSendPulse(fsmLSA1_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmLSA2_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmLSAbisHS1_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmLSAbisHS2_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmWsErkennung1_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmWsErkennung2_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmHSbisSep1_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmHSbisSep2_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmSepBisRut1_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmSepBisRut2_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmPassieren_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmSepBisLSEnde1_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(fsmSepBisLSEnde2_ID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, KEIN_FEHLER);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,LED_START_AUS );
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, LED_START_AUS);
		new (this) Betriebszustand;
	} else{
		new (this) Fehlerzustand;
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_AN);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, FEHLER_AN);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,LED_RESET_AN );
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, LED_RESET_AN);
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,LED_START_AUS );
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, LED_START_AUS);
		cout << "unbehandelter Fehler" << endl;
	}
}
