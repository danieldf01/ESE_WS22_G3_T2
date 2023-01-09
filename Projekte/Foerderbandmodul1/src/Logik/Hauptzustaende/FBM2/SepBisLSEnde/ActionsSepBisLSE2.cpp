/*
 * ActionsSepBisLSEnde.cpp
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */

#include "ActionsSepBisLSE2.h"

ActionsSepBisLSE2::~ActionsSepBisLSE2() {
}

void ActionsSepBisLSE2::setupConnection(){
	if ((logikID = name_open(LOGIK, NAME_FLAG_ATTACH_GLOBAL)) == -1) {
		perror("[FSM_SepBisLSE2] name_open failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE2::seperatorAn(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, TIMER_START_WEICHE) == -1) {
		perror("[FSM_SepBisLSE2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, SEP_AN) == -1) {
		perror("[FSM_SepBisLSE2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE2::seperatorAus(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, SEP_AUS) == -1) {
		perror("[FSM_SepBisLSE2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE2::fehlerHoch(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, FEHLER_HOCH) == -1) {
		perror("[FSM_SepBisLSE2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE2::fehlerRunter(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, FEHLER_RUNTER) == -1) {
		perror("[FSM_SepBisLSE2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE2::entferneWsPassieren(){
	wsListen->ws_passieren_2 = nullptr;
}

void ActionsSepBisLSE2::schnellRunter(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, SCHNELL_RUNTER_2) == -1) {
		perror("[FSM_SepBisLSE2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE2::deleteTimerVerschwunden(){
	zeitmanager->deleteTimer(wsListen->ws_passieren_2->getiD());
}

void ActionsSepBisLSE2::sendFBM2Bereit() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, FBM2_BEREIT) == -1) {
		perror("[FSM_LSAnfang2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisLSE2::eStop(){

}
