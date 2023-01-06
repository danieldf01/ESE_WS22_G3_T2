/*
 * ContextSepBisLSEnde.cpp
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */

#include "ContextSepBisLSE2.h"

using namespace std;

ContextSepBisLSE2::ContextSepBisLSE2(ActionsSepBisLSE2 *shared_action, WsListen *werkstueckListen, Zeitmanager *zeitmanagerFSM, KonfigurationsdateiManager *konfigManager) :
		actions(shared_action), wsListen(werkstueckListen), zeitmanager(zeitmanagerFSM), konfig(konfigManager) {

	qnetHandler = new QnetHandler();
	attach = qnetHandler->openServer(S_SEP_BIS_LSENDE2);

	actions->setupConnection();
	actions->setWsListen(wsListen);
	actions->setZeitmanager(zeitmanager);

	state = new WarteSepBisLSE2;
	state->setActions(actions);
	state->setWsListen(wsListen);
	state->setKonfig(konfig);
	state->setZeitmanager(zeitmanager);
	state->entry();
}

ContextSepBisLSE2::~ContextSepBisLSE2() {
	delete state;
}

void ContextSepBisLSE2::receiveSignal() {
	_pulse pulse;
	while (1) {

		int rcvid = MsgReceive(attach->chid, &pulse, sizeof(_pulse), NULL);

		if (rcvid == -1) { // Error occurred
			perror("[FSM_SepBisLSE2 MsgReceived failed");
		}
		if (rcvid == 0) { // Pulse was received
			switch (pulse.value.sival_int) {
			case LS_ENDE_AN:
				LsEAn();
				break;
			case LS_ENDE_AUS:
				LsEAus();
				break;
			case WS_PASSIEREN:
				WsPassieren();
				break;
			case ZEIT_WEICHE:
				WeicheSchliessen();
				break;
			case QUITTIERT:
				quittiert();
				break;
			case KEIN_FEHLER:
				keinFehler();
				break;
			case FEHLER_WS_VERSCHWUNDEN_SEP_BIS_LSE:
				fehlerVerschwunden();
				break;
			case E_STOP_AN:
				eStop();
				break;
			}
		}
		// handle name_open calls for this server
		if ((_IO_BASE <= pulse.type) && (pulse.type <= _IO_MAX)) {
			if (pulse.type == _IO_CONNECT) {
				cout << "[" << S_SEP_BIS_RUT1 << "]" << " received _IO_CONNECT via sync. message" << endl;
				MsgReply(rcvid, EOK, NULL, 0);
			}
		}
	}
}

void ContextSepBisLSE2::LsEAn(){
	state->LsEAn();
}

void ContextSepBisLSE2::LsEAus() {
	state->LsEAus();
}

void ContextSepBisLSE2::WsPassieren(){
	state->WsPassieren();
}

void ContextSepBisLSE2::WeicheSchliessen(){
	state->WeicheSchliessen();
}

void ContextSepBisLSE2::quittiert(){
	state->quittiert();
}

void ContextSepBisLSE2::keinFehler(){
	state->keinFehler();
}

void ContextSepBisLSE2::fehlerVerschwunden(){
	state->fehlerVerschwunden();
}

void ContextSepBisLSE2::eStop(){
	state->eStop();
}
