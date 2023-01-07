/*
 * ActionsPassieren.cpp
 *
 *  Created on: 07.01.2023
 *      Author: Daniel Drefs Fernandes
 */

#include "ActionsPassieren.h"

ActionsPassieren::~ActionsPassieren() {
}

void ActionsPassieren::setupConnection(){
	if ((logikID = name_open(LOGIK, NAME_FLAG_ATTACH_GLOBAL)) == -1) {
		perror("[FSM_Passieren] name_open failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsPassieren::seperatorAn(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, TIMER_START_WEICHE) == -1) {
		perror("[FSM_Passieren] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SEP_AN) == -1) {
		perror("[FSM_Passieren] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsPassieren::seperatorAus(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SEP_AUS) == -1) {
		perror("[FSM_Passieren] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsPassieren::WsAufWegZuLSE(){
	Werkstueck tempWs = wsListen->ws_list_passieren.front();
	wsListen->ws_list_passieren.pop_front();
	wsListen->ws_list_sep_bis_lsende.push_back(tempWs);
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, WS_AUF_WEG_ZU_LSE) == -1) {
		perror("[FSM_Passieren] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsPassieren::eStop(){
	wsListen->ws_list_sep_bis_lsende.clear();
}
