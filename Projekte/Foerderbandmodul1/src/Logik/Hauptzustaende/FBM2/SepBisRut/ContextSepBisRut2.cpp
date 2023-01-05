/*
 * ContextSepBisRut2.cpp
 *
 *  Created on: 11.12.2022
 *      Author: Daniel
 */
// DONE
#include "ContextSepBisRut2.h"

using namespace std;

ContextSepBisRut2::ContextSepBisRut2(ActionsSepBisRut2 *shared_action, WsListen *werkstueckListen, Zeitmanager *zeitmanagerFSM, KonfigurationsdateiManager *konfigManager) :
		actions(shared_action), wsListen(werkstueckListen), zeitmanager(zeitmanagerFSM), konfig(konfigManager) {

	qnetHandler = new QnetHandler();
	attach = qnetHandler->openServer(S_SEP_BIS_RUT2);

	actions->setupConnection();
	actions->setWsListen(wsListen);
	actions->setZeitmanager(zeitmanager);

	state = new WarteSepBisRut2;
	state->setActions(actions);
	state->setWsListen(wsListen);
	state->setKonfig(konfig);
	state->entry();
}

ContextSepBisRut2::~ContextSepBisRut2() {
	delete state;
}

void ContextSepBisRut2::receiveSignal() {
	_pulse pulse;
	while (1) {

		int rcvid = MsgReceive(attach->chid, &pulse, sizeof(_pulse), NULL);

		if (rcvid == -1) { // Error occurred
			perror("[FSM_SepBisRut2] MsgReceived failed");
		}
		if (rcvid == 0) { // Pulse was received
			switch (pulse.value.sival_int) {
			case LS_RUTSCHE_AN:
				LsRutAn();
				break;
			case WS_AUSSORTIEREN:
				WsAussortieren();
				break;
			case ZEIT_AUSWERFER:
				AuswerferEinfahren();
				break;
			case QUITTIERT:
				quittiert();
				break;
			case KEIN_FEHLER:
				keinFehler();
				break;
			case FEHLER_WS_VERSCHWUNDEN_SEP_BIS_RUT:
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
				cout << "[" << S_SEP_BIS_RUT2 << "]" << " received _IO_CONNECT via sync. message" << endl;
				MsgReply(rcvid, EOK, NULL, 0);
			}
		}
	}
}

void ContextSepBisRut2::LsRutAn() {
	state->LsRutAn();
}

void ContextSepBisRut2::WsAussortieren() {
	state->WsAussortieren();
}

void ContextSepBisRut2::AuswerferEinfahren() {
	state->AuswerferEinfahren();
}

void ContextSepBisRut2::quittiert() {
	state->quittiert();
}

void ContextSepBisRut2::keinFehler() {
	state->keinFehler();
}

void ContextSepBisRut2::Fverschwunden() {
	state->Fverschwunden();
}

void ContextSepBisRut2::eStop() {
	state->eStop();
}
