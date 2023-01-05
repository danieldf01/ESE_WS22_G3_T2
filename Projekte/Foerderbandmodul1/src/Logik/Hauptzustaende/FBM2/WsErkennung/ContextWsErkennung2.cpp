/*
 * ContextWsErkennung2.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "ContextWsErkennung2.h"

ContextWsErkennung2::ContextWsErkennung2(ActionsWsErkennung2 *shared_action, WsListen *werkstueckListen, Zeitmanager *zeitmanagerFSM) :
actions(shared_action), wsListen(werkstueckListen), zeitmanager(zeitmanagerFSM) {

	qnetHandler = new QnetHandler();
	attach = qnetHandler->openServer(S_WS_ERKENNUNG2);

	actions->setupConnection();
	actions->setWsListen(wsListen);
	actions->setZeitmanager(zeitmanager);

	state = new WartenWsErkennung2();
	state->setActions(actions);
	state->setWsListen(wsListen);
	state->setZeitmanager(zeitmanager);
	state->entry();

}

ContextWsErkennung2::~ContextWsErkennung2() {
	delete state;
}

void ContextWsErkennung2::receiveSignal() {
	_pulse pulse;
	while (1) {

		int rcvid = MsgReceive(attach->chid, &pulse, sizeof(_pulse), NULL);

		if (rcvid == -1) { // Error occurred
			perror("[FSM_WsErkennung2] MsgReceived failed");
		}
		if (rcvid == 0) { // Pulse was received
			switch (pulse.value.sival_int) {
			//TODO cases abfangen
			case WS_IN_HS:
				WSinHS();
				break;
			case WS_TYP:
				WsTyp();
				break;
			case QUITTIERT:
				quittiert();
				break;
			case KEIN_FEHLER:
				keinFehler();
				break;
			case FEHLER_HOEHENMESSUNG:
				fehlerHoehenmessung();
				break;
			case E_STOP_AN:
				eStop();
				break;
			}
		}
		// handle name_open calls for this server
		if ((_IO_BASE <= pulse.type) && (pulse.type <= _IO_MAX)) {
			if (pulse.type == _IO_CONNECT) {
				cout << "[" << S_WS_ERKENNUNG2 << "]"
						<< " received _IO_CONNECT via sync. message" << endl;
				MsgReply(rcvid, EOK, NULL, 0);
			}
		}
	}
}

void ContextWsErkennung2::WSinHS() {
	state->WSinHS();
}

void ContextWsErkennung2::WsTyp() {
	state->WsTyp();
}

void ContextWsErkennung2::quittiert() {
	state->quittiert();
}

void ContextWsErkennung2::keinFehler() {
	state->keinFehler();
}

void ContextWsErkennung2::fehlerHoehenmessung() {
	state->fehlerHoehenmessung();
}

void ContextWsErkennung2::eStop() {
	state->eStop();
}
