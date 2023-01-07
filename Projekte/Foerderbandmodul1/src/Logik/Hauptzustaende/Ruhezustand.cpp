 /*
 * Hauptzustand.cpp
 *
 *  Created on: 04.12.2022
 *      Author: User
 */

#include "Ruhezustand.h"

using namespace std;

void Ruhezustand::handlePulse(int code,int value){

	switch(code){

	case CODE_FBM_1: //pulse von FBM_1
		pulseFBM1(value);
		break;

	case CODE_FBM_2: //Pulse von FBM_2
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
void Ruhezustand::pulseFBM1(int value){
	switch(value){
	case T_START_AN:
		//TODO Starte Timer um zwischen Betriebsmodus&Service modus zu unterscheiden
		break;

	case T_START_AUS:
		cout << "switched to Betriebszustand"<< endl;
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL,BETRIEBSMODUS_AN );
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, BETRIEBSMODUS_AN);
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,STOP_RUNTER_1 );
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_2,STOP_RUNTER_2 );
		new (this) Betriebszustand;
		break;

	case E_STOP_AN:
		eStop(1);
		break;

	case SL_Q1_AN:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,SL_Q1_AN);
		break;

	case SL_Q1_AUS:
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,SL_Q1_AUS);
		break;

	case LS_RUTSCHE_AUS:
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,LS_RUTSCHE_AUS);
		break;

	case LS_RUTSCHE_AN:
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT,CODE_FBM_1,LS_RUTSCHE_AN);
		break;

		//Pulse fuer Motorsteuerung1
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

	//Pulse von Substates
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

	}
}

/**
 *
 * PULSE VON FBM2
 *
 */
void Ruhezustand::pulseFBM2(int value){
	switch (value) {

	case T_START_AN:
		//TODO Starte Timer um zwischen Betriebsmodus&Service modus zu unterscheiden
		break;

	case T_START_AUS:  		//active high+
		MsgSendPulse(inputID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, BETRIEBSMODUS_AN);
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, BETRIEBSMODUS_AN);
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, STOP_RUNTER_1);
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, STOP_RUNTER_2);
		new (this) Betriebszustand;
		break;

	case E_STOP_AN:
		eStop(2);
		break;

	case LS_RUTSCHE_AUS:	//active low+
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, LS_RUTSCHE_AUS);
		break;

	case LS_RUTSCHE_AN: //active low+
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, LS_RUTSCHE_AN);
		break;

		//Pulse fuer Motorsteuerung2
	case SCHNELL_HOCH_2:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, SCHNELL_HOCH_2);
		break;

	case SCHNELL_RUNTER_2:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, SCHNELL_RUNTER_2);
		break;

	case LANGSAM_HOCH_2:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2,
				LANGSAM_HOCH_2);
		break;

	case LANGSAM_RUNTER_2:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, LANGSAM_RUNTER_2);
		break;

	case STOP_HOCH_2:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, STOP_HOCH_2);
		break;

	case STOP_RUNTER_2:
		MsgSendPulse(motorID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, STOP_RUNTER_2);
		break;

	case MOT_LANGSAM_AN_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, MOTOR_LANGSAM_AN);
		break;

	case MOT_LANGSAM_AUS_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, MOTOR_LANGSAM_AUS);
		break;

	case MOT_R_AN_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, MOTOR_AN);
		break;

	case MOT_R_AUS_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, MOTOR_AUS);
		break;

	case MOT_STOP_AN_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, MOTOR_STOP_AN);
		MsgSendPulse(auswertungID2, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_STOP_AN);
		break;

	case MOT_STOP_AUS_2:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, MOTOR_STOP_AUS);
		MsgSendPulse(auswertungID2, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_STOP_AUS);
		break;

		//Pulse von substates fuer FBM2
	case WARNUNG_AUS:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, RUTSCHE_FREI);
		warnungsCount--;
		break;

	case WARNUNG_AN:
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, RUTSCHE_VOLL);
		warnungsCount++;
		break;

	case TIMER_RUTSCHE:
		MsgSendPulse(rutschenID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, TIMER_RUTSCHE);
		break;

	}
}

/**
 *
 * PULSE VON zeitFBM1
 *
 */
void Ruhezustand::pulseZeit1(int value){

}

/**
 *
 * PULSE VON zeitFBM2
 *
 */
void Ruhezustand::pulseZeit2(int value){

}

void Ruhezustand::updateAuswertung(){
	//TODO
//	hoehenauswertung1->hoehe_hoehes_ws_adc= dateiManager->get_value_of(Konfi_Codes::ADC_WS_HOCH_LEVEL_1);
//	hoehenauswertung2->hoehe_hoehes_ws_adc= dateiManager->get_value_of(Konfi_Codes::ADC_WS_HOCH_LEVEL_2);
//
//	hoehenauswertung1->hoehe_laufband_adc= dateiManager->get_value_of(Konfi_Codes::ADC_BAND_LEVEL_1);
//	hoehenauswertung2->hoehe_laufband_adc= dateiManager->get_value_of(Konfi_Codes::ADC_BAND_LEVEL_2);

}
void Ruhezustand::eStop(int estop){
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
	MsgSendPulse(fsmHSbisSep1_ID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmSepBisRut1_ID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmSepBisLSEnde1_ID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, E_STOP_AN);
	MsgSendPulse(fsmLSA2_ID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, E_STOP_AN);
	zeitFBM1->clearLists();
	zeitFBM2->clearLists();
	MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, ESTOP_AN);
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
