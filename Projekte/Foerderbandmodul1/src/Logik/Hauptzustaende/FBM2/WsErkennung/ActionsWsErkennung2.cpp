/*
 * ActionsWsErkennung2.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "ActionsWsErkennung2.h"

ActionsWsErkennung2::~ActionsWsErkennung2() {

}

void ActionsWsErkennung2::setupConnection(){
	if ((logikID = name_open(LOGIK, NAME_FLAG_ATTACH_GLOBAL)) == -1) {
		perror("[FSM_WsErkennung2] name_open failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsWsErkennung2::langsamRunter(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, LANGSAM_RUNTER_2) == -1) {
		perror("[FSM_WsErkennung2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsWsErkennung2::schnellRunter(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, SCHNELL_RUNTER_2) == -1) {
		perror("[FSM_WsErkennung2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsWsErkennung2::WSinHSbisSeperator(){
	zeitmanager->deleteTimer(wsListen->ws_Hoehensensor_2.getiD());

	Werkstueck tempWS = wsListen->ws_Hoehensensor_2;
	tempWS.setTimestamp(zeitmanager->getTime());
	wsListen->ws_hs_bis_seperator_2 = tempWS;
	wsListen->ws_Hoehensensor_2.~Werkstueck();

//	wsListen->ws_Hoehensensor_2->setTimestamp(zeitmanager->getTime());
//	wsListen->ws_hs_bis_seperator_2 = wsListen->ws_Hoehensensor_2;
//	wsListen->ws_Hoehensensor_2 = nullptr;

	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, WS_IN_HS_BIS_SEPERATOR) == -1) {
		perror("[FSM_WsErkennung2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsWsErkennung2::fehlerHoch(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, FEHLER_HOCH) == -1) {
		perror("[FSM_WsErkennung2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsWsErkennung2::fehlerRunter(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, FEHLER_RUNTER) == -1) {
		perror("[FSM_WsErkennung2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsWsErkennung2::deleteWsHoehensensor(){
	wsListen->ws_Hoehensensor_2.~Werkstueck();
}

void ActionsWsErkennung2::sendFBM2Bereit() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, FBM2_BEREIT) == -1) {
		perror("[FSM_LSAnfang2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsWsErkennung2::speicherWSTyp() {
	Werkstueck tempWS = wsListen->ws_Hoehensensor_2;
	wsTyp = tempWS.getWsTyp();
}

void ActionsWsErkennung2::checkWSueberschlagen() {
	Werkstueck tempWS = wsListen->ws_Hoehensensor_2;

	if(wsTyp == tempWS.getWsTyp()){
		wsListen->ueberschlagen = false;
	} else {
		wsListen->ueberschlagen = true;
	}
	wsListen->ws_Hoehensensor_2 = tempWS;
}

void ActionsWsErkennung2::eStop(){
	wsListen->ws_hs_bis_seperator_2.~Werkstueck();
}
