/*
 * ActionsLSAbisHS.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "ActionsLSAbisHS1.h"

ActionsLSAbisHS1::~ActionsLSAbisHS1() {

}

void ActionsLSAbisHS1::setupConnection() {
	if ((logikID = name_open(LOGIK, NAME_FLAG_ATTACH_GLOBAL)) == -1) {
		perror("[FSM_LSAnfangBisHS] name_open failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSAbisHS1::WSinHS() {
	//loesche den timer fuer den WS verschwunden error, da das WS den HS erreicht hat
	zeitmanager->deleteTimer(wsListen->ws_list_LSAnfang_bis_HS.front().getiD());

	Werkstueck temp_ws = wsListen->ws_list_LSAnfang_bis_HS.front();
	wsListen->ws_list_LSAnfang_bis_HS.pop_front();
	temp_ws.setTimestamp(zeitmanager->getTime());
	wsListen->ws_Hoehensensor_1 = temp_ws;

//	cout << "ActionsLSAbisHS1 Ws HS timestamp: " << wsListen->ws_Hoehensensor_1.getTimestamp() << endl;
//	cout << "ActionsLSAbisHS1 Ws HS ID: " << wsListen->ws_Hoehensensor_1.getiD() << endl;

	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, WS_IN_HS) == -1) {
		perror("[FSM_LSAnfangBisHS] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, LANGSAM_HOCH_1) == -1) {
		perror("[FSM_LSAnfangBisHS] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSAbisHS1::fehlerHoch() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_HOCH) == -1) {
		perror("[FSM_LSAnfangBisHS] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSAbisHS1::fehlerRunter() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_RUNTER) == -1) {
		perror("[FSM_LSAnfangBisHS] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSAbisHS1::entferneWsLSAbisHS() {
	wsListen->ws_list_LSAnfang_bis_HS.pop_front();
}

void ActionsLSAbisHS1::schnellRunter() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SCHNELL_RUNTER_1) == -1) {
		perror("[FSM_LSAnfangBisHS] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSAbisHS1::HSleeren() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, HS_LEEREN) == -1) {
		perror("[FSM_LSAnfangBisHS] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSAbisHS1::eStop() {
	wsListen->ws_Hoehensensor_1.~Werkstueck();
}
