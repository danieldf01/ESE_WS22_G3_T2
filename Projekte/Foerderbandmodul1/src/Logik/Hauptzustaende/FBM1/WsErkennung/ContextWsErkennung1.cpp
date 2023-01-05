/*
 * ContextWsErkennung1.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "ContextWsErkennung1.h"

ContextWsErkennung1::ContextWsErkennung1(ActionsWsErkennung1 *shared_action,
		WsListen *werkstueckListen, Zeitmanager *zeitmanagerFSM) :
		actions(shared_action), wsListen(werkstueckListen), zeitmanager(
				zeitmanagerFSM) {

	qnetHandler = new QnetHandler();
	attach = qnetHandler->openServer(S_WS_ERKENNUNG1);

	actions->setupConnection();
	actions->setWsListen(wsListen);
	actions->setZeitmanager(zeitmanager);

	state = new WartenWsErkennung1();
	state->setActions(actions);
	state->setWsListen(wsListen);
	state->setZeitmanager(zeitmanager);
	state->entry();

}

ContextWsErkennung1::~ContextWsErkennung1() {
	delete state;
}

void ContextWsErkennung1::receiveSignal() {
	_pulse pulse;
	while (1) {

		int rcvid = MsgReceive(attach->chid, &pulse, sizeof(_pulse), NULL);

		if (rcvid == -1) { // Error occurred
			perror("[FSM_WsErkennung] MsgReceived failed");
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
				cout << "[" << S_WS_ERKENNUNG1 << "]"
						<< " received _IO_CONNECT via sync. message" << endl;
				MsgReply(rcvid, EOK, NULL, 0);
			}
		}
	}
}

void ContextWsErkennung1::WSinHS() {
	state->WSinHS();
}

void ContextWsErkennung1::WsTyp() {
	state->WsTyp();
}

void ContextWsErkennung1::quittiert() {
	state->quittiert();
}

void ContextWsErkennung1::keinFehler() {
	state->keinFehler();
}

void ContextWsErkennung1::fehlerHoehenmessung() {
	state->fehlerHoehenmessung();
}

void ContextWsErkennung1::eStop() {
	state->eStop();
}
