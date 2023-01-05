/*
 * ActionsWsNichtAussortierbar.cpp
 *
 *  Created on: 21.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "ActionsWsNichtAussortierbar.h"

ActionsWsNichtAussortierbar::~ActionsWsNichtAussortierbar() {

}

void ActionsWsNichtAussortierbar::setupConnection(){
	if ((logikID = name_open(LOGIK, NAME_FLAG_ATTACH_GLOBAL)) == -1) {
		perror("[FSM_WsNichtAussortierbar] name_open failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsWsNichtAussortierbar::fehlerHoch(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,
	CODE_FBM_1, FEHLER_HOCH) == -1) {
		perror("[FSM_WsNichtAussortierbar] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsWsNichtAussortierbar::fehlerRunter(){
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,
	CODE_FBM_1, FEHLER_RUNTER) == -1) {
		perror("[FSM_WsNichtAussortierbar] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}
