/*
 * ContextLSA2.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "ContextLSA2.h"

using namespace std;
// TODO Konstruktor anpassen
ContextLSA2::ContextLSA2(ActionsLSA2 *shared_action, WsListen *werkstueckListen, Zeitmanager *zeitmanagerFSM) :
		actions(shared_action), wsListen(werkstueckListen), zeitmanager(zeitmanagerFSM) {

	qnetHandler = new QnetHandler();
	attach = qnetHandler->openServer(S_LSANFANG2);

	actions->setupConnection();
	actions->setWsListen(wsListen);
	actions->setZeitmanager(zeitmanager);

	state = new WarteAufFBM2();
	state->setActions(actions);
	state->entry();
}

ContextLSA2::~ContextLSA2() {
	delete state;
}

void ContextLSA2::receiveSignal() {
	_pulse pulse;
	while (1) {

		int rcvid = MsgReceive(attach->chid, &pulse, sizeof(_pulse), NULL);

		if (rcvid == -1) { // Error occurred
			perror("[FSM_LSAnfang2] MsgReceived failed");
		}
		if (rcvid == 0) { // Pulse was received
			switch (pulse.value.sival_int) {
				case FBM1_BEREIT:
					fbm1Bereit();
					break;
				case FBM2_BEREIT:
					fbm2Bereit();
					break;
				case LS_ANFANG_AN:
					lsAnfangAn();
					break;
				case FBM1_WS_LOSGESCHICKT:
					fbm1WsLosgeschickt();
					break;
				case FBM1_WS_UEBERGEBEN:
					fbm1WsUebergeben();
					break;
				case LS_ANFANG_AUS:
					lsAnfangAus();
					break;
				case QUITTIERT:
					quittiert();
					break;
				case KEIN_FEHLER:
					keinFehler();
					break;
				case FEHLER_WS_VERSCHWUNDEN_LSA2:
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
				// cout << S_LSANFANG << " received _IO_CONNECT via sync. message"<< endl;
				MsgReply(rcvid, EOK, NULL, 0);
			}
		}
	}
}

void ContextLSA2::lsAnfangAn() {
	state->lsAnfangAn();
}

void ContextLSA2::lsAnfangAus() {
	state->lsAnfangAus();
}

void ContextLSA2::fbm1WsLosgeschickt() {
	state->fbm1WsLosgeschickt();
}

void ContextLSA2::fbm1WsUebergeben() {
	state->fbm1WsUebergeben();
}

void ContextLSA2::quittiert() {
	state->quittiert();
}

void ContextLSA2::keinFehler() {
	state->keinFehler();
}

void ContextLSA2::fbm1Bereit() {
	state->fbm1Bereit();
}

void ContextLSA2::fbm2Bereit() {
	state->fbm2Bereit();
}

void ContextLSA2::fehlerVerschwunden(){
	state->fehlerVerschwunden();
}

void ContextLSA2::eStop() {
	state->eStop();
}
