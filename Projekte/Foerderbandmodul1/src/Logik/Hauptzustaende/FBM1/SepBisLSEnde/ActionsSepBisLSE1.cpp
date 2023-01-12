/*
 * ActionsSepBisLSEnde.cpp
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */

#include "ActionsSepBisLSE1.h"

ActionsSepBisLSE1::~ActionsSepBisLSE1() {
}

void ActionsSepBisLSE1::setupConnection(){
	if ((logikID = name_open(LOGIK, NAME_FLAG_ATTACH_GLOBAL)) == -1) {
		perror("[FSM_SepBisLSE1] name_open failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE1::fehlerHoch(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_HOCH) == -1) {
		perror("[FSM_SepBisLSE1] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE1::fehlerRunter(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_RUNTER) == -1) {
		perror("[FSM_SepBisLSE1] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE1::entferneWsPassieren(){
	wsListen->ws_list_sep_bis_lsende.pop_front();
}

void ActionsSepBisLSE1::schnellRunter(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SCHNELL_RUNTER_1) == -1) {
		perror("[FSM_SepBisLSE1] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE1::stopHoch(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, STOP_HOCH_1) == -1) {
		perror("[FSM_SepBisLSE1] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE1::stopRunter(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, STOP_RUNTER_1) == -1) {
		perror("[FSM_SepBisLSE1] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE1::FBM1bereit(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FBM1_BEREIT) == -1) {
		perror("[FSM_SepBisLSE1] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE1::FBM1WsLosgeschickt(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FBM1_WS_LOSGESCHICKT) == -1) {
		perror("[FSM_SepBisLSE1] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE1::FBM1WsUebergeben(){

	Werkstueck wsTemp = wsListen->ws_list_sep_bis_lsende.front();
	wsListen->ws_ls_anfang_2 = wsTemp;
	wsListen->ws_list_sep_bis_lsende.pop_front();

//	wsListen->ws_ls_anfang_2 = &(wsListen->ws_list_sep_bis_lsende.front());
//	wsListen->ws_list_sep_bis_lsende.pop_front();

	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FBM1_WS_UEBERGEBEN) == -1) {
		perror("[FSM_SepBisLSE1] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE1::deleteTimerVerschwunden(){
	zeitmanager->deleteTimer(wsListen->ws_list_sep_bis_lsende.front().getiD());
}

void ActionsSepBisLSE1::eStop(){
	wsListen->ws_ls_anfang_2.~Werkstueck();
}
