/*
 * ActionsSepBisRut1.cpp
 *
 *  Created on: 11.12.2022
 *      Author: Daniel
 */
// DONE
#include "ActionsSepBisRut1.h"

ActionsSepBisRut1::~ActionsSepBisRut1() {

}

void ActionsSepBisRut1::setupConnection() {
	if ((logikID = name_open(LOGIK, NAME_FLAG_ATTACH_GLOBAL)) == -1) {
		perror("[FSM_SepBisRut] name_open failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisRut1::seperatorAn(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, TIMER_START_AUSWERFER) == -1) {
		perror("[FSM_SepBisRut] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SEP_AN) == -1) {
		perror("[FSM_SepBisRut] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisRut1::seperatorAus(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SEP_AUS) == -1) {
		perror("[FSM_SepBisRut] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisRut1::fehlerHoch() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_HOCH) == -1) {
		perror("[FSM_SepBisRut] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisRut1::fehlerRunter() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_RUNTER) == -1) {
		perror("[FSM_SepBisRut] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisRut1::schnellRunter() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SCHNELL_RUNTER_1) == -1) {
		perror("[FSM_SepBisRut] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsSepBisRut1::zerstoereWsAussortieren() {
	wsListen->ws_list_aussortieren.pop_front();
}

void ActionsSepBisRut1::deleteTimerVerschwunden(){
	zeitmanager->deleteTimer(wsListen->ws_list_aussortieren.front().getiD());
}
