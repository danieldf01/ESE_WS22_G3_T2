/*
 * ContextLSAnfang.cpp
 *
 *  Created on: 11.12.2022
 *      Author: Daniel
 */

#include "ContextLSA1.h"

using namespace std;

ContextLSA1::ContextLSA1(ActionsLSA1 *shared_action, WsListen *werkstueckListen, Zeitmanager *zeitmanagerFSM) :
		actions(shared_action), wsListen(werkstueckListen), zeitmanager(zeitmanagerFSM) {

	qnetHandler = new QnetHandler();
	attach = qnetHandler->openServer(S_LSANFANG1);

	actions->setupConnection();
	actions->setWsListen(wsListen);
	actions->setZeitmanager(zeitmanager);

	state = new WarteAufWsLSA1();
	state->setActions(actions);
	state->entry();
}

ContextLSA1::~ContextLSA1() {
	delete state;
}

void ContextLSA1::receiveSignal() {
	_pulse pulse;
	while (1) {

		int rcvid = MsgReceive(attach->chid, &pulse, sizeof(_pulse), NULL);

		if (rcvid == -1) { // Error occurred
			perror("[FSM_LSAnfang] MsgReceived failed");
			exit(EXIT_FAILURE);
		}
		if (rcvid == 0) { // Pulse was received
			switch (pulse.value.sival_int) {
			case LS_ANFANG_AN:
				LSan();
				break;
			case LS_ANFANG_AUS:
				LSaus();
				break;
			case QUITTIERT:
				quittiert();
				break;
			case KEIN_FEHLER:
				keinFehler();
				break;
			case E_STOP_AN:
				eStop();
				break;
			case FEHLER_WS_STECKT_FEST_LSA:
				WSstecktFest();
				break;
			case ZEIT_WS_ABSTAND:
				timerAbstand();
				break;
			}
		}
		// handle name_open calls for this server
		if ((_IO_BASE <= pulse.type) && (pulse.type <= _IO_MAX)) {
			if (pulse.type == _IO_CONNECT) {
				cout << S_LSANFANG1 << " received _IO_CONNECT via sync. message" << endl;
				MsgReply(rcvid, EOK, NULL, 0);
			}
		}
	}
}

void ContextLSA1::LSan() {
	state->LSan();
}

void ContextLSA1::LSaus() {
	state->LSaus();
}

void ContextLSA1::WSstecktFest() {
	state->WSstecktFest();
}

void ContextLSA1::quittiert() {
	state->quittiert();
}

void ContextLSA1::keinFehler() {
	state->keinFehler();
}

void ContextLSA1::eStop() {
	state->eStop();
}

void ContextLSA1::timerAbstand() {
	state->timerAbstand();
}

