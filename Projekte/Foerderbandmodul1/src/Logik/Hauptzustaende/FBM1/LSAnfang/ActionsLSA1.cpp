/*
 * ActionsLSAnfang.cpp
 *
 *  Created on: 11.12.2022
 *      Author: Daniel
 */

#include "ActionsLSA1.h"

using namespace std;

ActionsLSA1::ActionsLSA1() {
	wsID = 1;
}

ActionsLSA1::~ActionsLSA1() {

}


void ActionsLSA1::setupConnection() {
	if ((logikID = name_open(LOGIK, NAME_FLAG_ATTACH_GLOBAL)) == -1) {
		perror("[FSM_LSAnfang] name_open failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSA1::schnellHoch() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SCHNELL_HOCH_1) == -1) {
		perror("[FSM_LSAnfang] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSA1::erstelleWS() {
//	werkstueck = new Werkstueck(wsID, zeitmanager->getTime());
	Werkstueck tempWS(wsID, zeitmanager->getTime());
	wsListen->ws_LSAnfang = tempWS;

//	cout << "ActionsLSA1 tempWS timestamp: " << tempWS.getTimestamp() << endl;
//	cout << "ActionsLSA1 WsLSA timestamp: " << wsListen->ws_LSAnfang.getTimestamp() << endl;
//	cout << "ActionsLSA1 tempWS ID: " << tempWS.getiD() << endl;
//	cout << "ActionsLSA1 WsLSA ID: " << wsListen->ws_LSAnfang.getiD() << endl;

//	werkstueck = nullptr;

//	cout << "ActionsLSA1 WsLSA ID: " << wsListen->ws_LSAnfang.getiD() << endl;

	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, WS_ERSTELLT) == -1) {
		perror("[FSM_LSAnfang] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
	wsID++;
}

void ActionsLSA1::schnellRunter() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SCHNELL_RUNTER_1) == -1) {
		perror("[FSM_LSAnfang] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSA1::WSinLSAbisHS() {
	//loesche den error timer, da das Werkstueck nicht festhaengt
	zeitmanager->deleteTimer(wsListen->ws_LSAnfang.getiD());

	//gib dem Werkstueck einen aktuellen Timestamp und pack es in die Liste fuer die naechste FSM
	Werkstueck tempWS = wsListen->ws_LSAnfang;
	tempWS.setTimestamp(zeitmanager->getTime());
	wsListen->ws_list_LSAnfang_bis_HS.push_back(tempWS);
	wsListen->ws_LSAnfang.~Werkstueck();

//	cout << "ActionsLSA1 Ws LSAbisHS timestamp: " << wsListen->ws_list_LSAnfang_bis_HS.front.getTimestamp() << endl;
//	cout << "ActionsLSA1 Ws LSAbisHS ID: " << wsListen->ws_list_LSAnfang_bis_HS.front.getiD() << endl;

	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, WS_IN_LS_A_BIS_HS) == -1) {
		perror("[FSM_LSAnfang] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSA1::fehlerHoch() {
	wsListen->ws_LSAnfang.~Werkstueck();

	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_HOCH) == -1) {
		perror("[FSM_LSAnfang] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSA1::fehlerRunter() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, FEHLER_RUNTER) == -1) {
		perror("[FSM_LSAnfang] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSA1::eStop() {
	werkstueck = nullptr;
	wsListen->ws_LSAnfang.~Werkstueck();
	wsListen->ws_list_LSAnfang_bis_HS.clear();
}

void ActionsLSA1::slq1_an() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SL_Q1_AN) == -1) {
		perror("[FSM_LSAnfang] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}

void ActionsLSA1::slq1_aus() {
	if (MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, SL_Q1_AUS) == -1) {
		perror("[FSM_LSAnfang] MsgSendPulse failed");
		exit(EXIT_FAILURE);
	}
}
