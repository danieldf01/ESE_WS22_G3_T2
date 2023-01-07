/*
 * ActionsLSAbisHS2.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "ActionsLSAbisHS2.h"

ActionsLSAbisHS2::~ActionsLSAbisHS2() {

}

void ActionsLSAbisHS2::setupConnection() {
	if ((logikID = name_open(LOGIK, NAME_FLAG_ATTACH_GLOBAL)) == -1) {
		perror("[FSM_LSAnfangBisHS2] name_open failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSAbisHS2::WSinHS() {
	cout << "[FBM2] ActionsLSAbisHS2" << endl;

	//loesche den error timer, da das Werkstueck nicht festhaengt
	zeitmanager->deleteTimer(wsListen->ws_ls_anfang_bis_hs_2->getiD());

	//gib dem Werkstueck einen aktuellen Timestamp und pack es in die Liste fuer die naechste FSM
	wsListen->ws_ls_anfang_bis_hs_2->setTimestamp(zeitmanager->getTime());
	wsListen->ws_Hoehensensor_2 = wsListen->ws_ls_anfang_bis_hs_2;
	wsListen->ws_ls_anfang_bis_hs_2 = nullptr;

	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, WS_IN_HS) == -1) {
		perror("[FSM_LSAnfangBisHS] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, LANGSAM_HOCH_2) == -1) {
		perror("[FSM_LSAnfangBisHS] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSAbisHS2::fehlerHoch() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, FEHLER_HOCH) == -1) {
		perror("[FSM_LSAnfangBisHS] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSAbisHS2::fehlerRunter() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, FEHLER_RUNTER) == -1) {
		perror("[FSM_LSAnfangBisHS] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSAbisHS2::entferneWsLSAbisHS() {
	wsListen->ws_ls_anfang_bis_hs_2 = nullptr;
}

void ActionsLSAbisHS2::schnellRunter() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, SCHNELL_RUNTER_2) == -1) {
		perror("[FSM_LSAnfangBisHS] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSAbisHS2::HSleeren() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, HS_LEEREN) == -1) {
		perror("[FSM_LSAnfangBisHS] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSAbisHS2::sendFBM2Bereit() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_2, FBM2_BEREIT) == -1) {
		perror("[FSM_LSAnfang2] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSAbisHS2::eStop() {
	wsListen->ws_Hoehensensor_2 = nullptr;
}
