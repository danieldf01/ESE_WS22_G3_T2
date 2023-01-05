/*
 * ActionsLSA2.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "ActionsLSA2.h"

ActionsLSA2::ActionsLSA2() {

}

ActionsLSA2::~ActionsLSA2() {

}

void ActionsLSA2::setupConnection() {
	if ((logikID = name_open(LOGIK, NAME_FLAG_ATTACH_GLOBAL)) == -1) {
		perror("[FSM_LSAnfang2] name_open failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSA2::WSinLSAbisHS() {
	//loesche den error timer, da das Werkstueck nicht festhaengt
	zeitmanager->deleteTimer(wsListen->ws_ls_anfang_2->getiD());

	//gib dem Werkstueck einen aktuellen Timestamp und pack es in die Liste fuer die naechste FSM
	wsListen->ws_ls_anfang_2->setTimestamp(zeitmanager->getTime());
	wsListen->ws_ls_anfang_bis_hs_2 = wsListen->ws_ls_anfang_2;
	wsListen->ws_ls_anfang_2 = nullptr;

	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, WS_IN_LS_A_BIS_HS) == -1) {
		perror("[FSM_LSAnfang2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSA2::schnellHoch() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, SCHNELL_HOCH_2) == -1) {
		perror("[FSM_LSAnfang2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSA2::schnellRunter() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, SCHNELL_RUNTER_2) == -1) {
		perror("[FSM_LSAnfang2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSA2::schnellRunter1() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SCHNELL_RUNTER_1) == -1) {
		perror("[FSM_LSAnfang2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSA2::fehlerHoch() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, FEHLER_HOCH) == -1) {
		perror("[FSM_LSAnfang2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSA2::fehlerRunter() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, FEHLER_RUNTER) == -1) {
		perror("[FSM_LSAnfang2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSA2::sendFBM2Bereit() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, FBM2_BEREIT) == -1) {
		perror("[FSM_LSAnfang2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSA2::entferneWsLSA2(){
	wsListen->ws_ls_anfang_2 = nullptr;
}

void ActionsLSA2::eStop() {
	wsListen->ws_ls_anfang_bis_hs_2 = nullptr;
}
