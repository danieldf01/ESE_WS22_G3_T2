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
	//loesche den timer fuer den WS verschwunden error, da das WS den HS erreicht hat
//	zeitmanager->deleteTimer(wsListen->ws_list_LSAnfang_bis_HS_2.front().getiD());
//
//	//gib das Werkstueck, das den HS erreicht hat, an die naechste FSM weiter
//	//wsListen->ws_Hoehensensor_1 = &(wsListen->ws_list_LSAnfang_bis_HS.front()); // TODO Hier mit getter ersetzt
//	wsListen->setWsHoehensensor2(&(wsListen->ws_list_LSAnfang_bis_HS_2.front()));
//	wsListen->ws_list_LSAnfang_bis_HS_2.pop_front();
//	//wsListen->ws_Hoehensensor_1->setTimestamp(zeitmanager->getTime()); // TODO Hier mit getter ersetzt
//	wsListen->getWsHoehensensor2()->setTimestamp(zeitmanager->getTime());
//
//	cout << "ACTION Zeit vor WS_IN_HS Send" << wsListen->getWsHoehensensor2()->getTimestamp() << endl;

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
//	wsListen->ws_list_LSAnfang_bis_HS_2.pop_front();
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

void ActionsLSAbisHS2::eStop() {
	wsListen->ws_Hoehensensor_2 = nullptr;
}
