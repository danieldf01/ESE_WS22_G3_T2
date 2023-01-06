/*
 * ContextLSAbisHS2.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "ContextLSAbisHS2.h"

ContextLSAbisHS2::ContextLSAbisHS2(ActionsLSAbisHS2 *shared_action,
		WsListen *werkstueckListen, Zeitmanager *zeitmanagerFSM) :
		actions(shared_action), wsListen(werkstueckListen), zeitmanager(
				zeitmanagerFSM) {

	qnetHandler = new QnetHandler();
	attach = qnetHandler->openServer(S_LSA_BIS_HS2);

	actions->setupConnection();
	actions->setWsListen(wsListen);
	actions->setZeitmanager(zeitmanager);

	state = new WartenLSAbisHS2();
	state->setActions(actions);
	state->setWsListen(wsListen);
	state->setZeitmanager(zeitmanager);
	state->entry();

}

ContextLSAbisHS2::~ContextLSAbisHS2() {
	delete state;
}

void ContextLSAbisHS2::receiveSignal() {
	_pulse pulse;
	while (1) {

		int rcvid = MsgReceive(attach->chid, &pulse, sizeof(_pulse), NULL);

		if (rcvid == -1) { // Error occurred
			perror("[FSM_LSAnfangBisHS] MsgReceived failed");
		}
		if (rcvid == 0) { // Pulse was received
			switch (pulse.value.sival_int) {
			//TODO cases abfangen
			case WS_IN_LS_A_BIS_HS:
				WSinLSAbisHS();
				break;
			case HS_AKTIV:
				HSaktiv();
				break;
			case QUITTIERT:
				quittiert();
				break;
			case KEIN_FEHLER:
				keinFehler();
				break;
			case FEHLER_WS_VERSCHWUNDEN:
				Fverschwunden();
				break;
			case E_STOP_AN:
				eStop();
				break;
			}
		}
		// handle name_open calls for this server
		if ((_IO_BASE <= pulse.type) && (pulse.type <= _IO_MAX)) {
			if (pulse.type == _IO_CONNECT) {
				cout << "[" << S_LSA_BIS_HS1 << "]"
						<< " received _IO_CONNECT via sync. message" << endl;
				MsgReply(rcvid, EOK, NULL, 0);
			}
		}
	}
}

void ContextLSAbisHS2::WSinLSAbisHS() {
	state->WSinLSAbisHS();
}

void ContextLSAbisHS2::HSaktiv() {
	state->HSaktiv();
}

void ContextLSAbisHS2::quittiert() {
	state->quittiert();
}

void ContextLSAbisHS2::keinFehler() {
	state->keinFehler();
}

void ContextLSAbisHS2::Fverschwunden() {
	state->Fverschwunden();
}

void ContextLSAbisHS2::eStop() {
	state->eStop();
}
