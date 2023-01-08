/*
 * EStop1.cpp
 *
 *  Created on: Dec 8, 2022
 *      Author: bardi
 */

#include "EStop.h"

void EStop::handlePulse(int code,int value){
	switch(code){

		case CODE_FBM_1: //pulse von FBM1
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
void EStop::pulseFBM1(int value) {
	switch (value) {

	case E_STOP_AUS: //active low
		eStop1 = false;
		MsgSendPulse(kommID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, ESTOP_AUS);
		break;

	case E_STOP_AN:
		eStop1 = true;
		break;

	case T_RESET_AUS: //active high
		if (!eStop2 && !eStop1) {
			MsgSendPulse(auswertungID1, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, MOTOR_STOP_AUS);
			MsgSendPulse(auswertungID2, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL, MOTOR_STOP_AUS);

			wsListen->sortierReihenfolge.push_back(dateiManager->get_value_of(Konfi_Codes::WS_Reihung_Nr_1));
			wsListen->sortierReihenfolge.push_back(dateiManager->get_value_of(Konfi_Codes::WS_Reihung_Nr_2));
			wsListen->sortierReihenfolge.push_back(dateiManager->get_value_of(Konfi_Codes::WS_Reihung_Nr_3));

			wsListen->sortierReihenfolge2.push_back(dateiManager->get_value_of(Konfi_Codes::WS_Reihung_Nr_1));
			wsListen->sortierReihenfolge2.push_back(dateiManager->get_value_of(Konfi_Codes::WS_Reihung_Nr_2));
			wsListen->sortierReihenfolge2.push_back(dateiManager->get_value_of(Konfi_Codes::WS_Reihung_Nr_3));
			new (this) Ruhezustand;
		}
		break;
	}
}

/**
 *
 * PULSE VON FBM2
 *
 */
void EStop::pulseFBM2(int value){
	switch (value) {

	case E_STOP_AN:  		//active low
		eStop2 = true;
		break;

	case E_STOP_AUS:
		eStop2 = false;
		break;

	case T_RESET_AUS: //active high
		if (!eStop2 && !eStop1) {
			MsgSendPulse(auswertungID1, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_STOP_AUS);
			MsgSendPulse(auswertungID2, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL, MOTOR_STOP_AUS);

			wsListen->sortierReihenfolge.push_back(dateiManager->get_value_of(Konfi_Codes::WS_Reihung_Nr_1));
			wsListen->sortierReihenfolge.push_back(dateiManager->get_value_of(Konfi_Codes::WS_Reihung_Nr_2));
			wsListen->sortierReihenfolge.push_back(dateiManager->get_value_of(Konfi_Codes::WS_Reihung_Nr_3));

			wsListen->sortierReihenfolge2.push_back(dateiManager->get_value_of(Konfi_Codes::WS_Reihung_Nr_1));
			wsListen->sortierReihenfolge2.push_back(dateiManager->get_value_of(Konfi_Codes::WS_Reihung_Nr_2));
			wsListen->sortierReihenfolge2.push_back(dateiManager->get_value_of(Konfi_Codes::WS_Reihung_Nr_3));
			new (this) Ruhezustand;
		}
		break;
	}
}

/**
 *
 * PULSE VON zeitFBM1
 *
 */
void EStop::pulseZeit1(int value){

}

/**
 *
 * PULSE VON zeitFBM2
 *
 */
void EStop::pulseZeit2(int value){

}

void EStop::updateAuswertung(){

}

void EStop::eStop(int estop){

}
