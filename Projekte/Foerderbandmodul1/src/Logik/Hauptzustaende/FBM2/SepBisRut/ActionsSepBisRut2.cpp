/*
 * ActionsSepBisRut2.cpp
 *
 *  Created on: 11.12.2022
 *      Author: Daniel
 */
// DONE
#include "ActionsSepBisRut2.h"

ActionsSepBisRut2::~ActionsSepBisRut2() {

}

void ActionsSepBisRut2::setupConnection() {
	if ((logikID = name_open(LOGIK, NAME_FLAG_ATTACH_GLOBAL)) == -1) {
		perror("[FSM_SepBisRut2] name_open failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisRut2::seperatorAn(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, TIMER_START_AUSWERFER) == -1) {
		perror("[FSM_SepBisRut] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, SEP_AN) == -1) {
		perror("[FSM_SepBisRut2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisRut2::seperatorAus(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, SEP_AUS) == -1) {
		perror("[FSM_SepBisRut2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisRut2::fehlerHoch() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, FEHLER_HOCH) == -1) {
		perror("[FSM_SepBisRut2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisRut2::fehlerRunter() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, FEHLER_RUNTER) == -1) {
		perror("[FSM_SepBisRut2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisRut2::schnellRunter() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SCHNELL_RUNTER_1) == -1) {
		perror("[FSM_SepBisRut] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisRut2::zerstoereWsAussortieren() {
	wsListen->ws_list_aussortieren.pop_front();
}

void ActionsSepBisRut2::deleteTimerVerschwunden(){
	zeitmanager->deleteTimer(wsListen->ws_list_aussortieren.front().getiD());
}
