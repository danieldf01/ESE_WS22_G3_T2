/*
 * ActionsWsErkennung1.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "ActionsWsErkennung1.h"

ActionsWsErkennung1::~ActionsWsErkennung1() {

}

void ActionsWsErkennung1::setupConnection(){
	if ((logikID = name_open(LOGIK, NAME_FLAG_ATTACH_GLOBAL)) == -1) {
		perror("[FSM_WsErkennung] name_open failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsWsErkennung1::langsamRunter(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,
	CODE_FBM_1, LANGSAM_RUNTER_1) == -1) {
		perror("[FSM_WsErkennung] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsWsErkennung1::schnellRunter(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,
	CODE_FBM_1, SCHNELL_RUNTER_1) == -1) {
		perror("[FSM_WsErkennung] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsWsErkennung1::WSinHSbisSeperator(){
	zeitmanager->deleteTimer(wsListen->ws_Hoehensensor_1->getiD());
	wsListen->ws_Hoehensensor_1->setTimestamp(zeitmanager->getTime());
	wsListen->ws_list_HS_bis_Seperator.push_back(*(wsListen->ws_Hoehensensor_1));
	wsListen->ws_Hoehensensor_1 = nullptr;
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,
	CODE_FBM_1, WS_IN_HS_BIS_SEPERATOR) == -1) {
		perror("[FSM_WsErkennung] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsWsErkennung1::fehlerHoch(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,
	CODE_FBM_1, FEHLER_HOCH) == -1) {
		perror("[FSM_WsErkennung] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsWsErkennung1::fehlerRunter(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,
	CODE_FBM_1, FEHLER_RUNTER) == -1) {
		perror("[FSM_WsErkennung] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsWsErkennung1::deleteWsHoehensensor(){
	wsListen->ws_Hoehensensor_1 = nullptr;
}

void ActionsWsErkennung1::eStop(){
	wsListen->ws_list_HS_bis_Seperator.clear();
}
