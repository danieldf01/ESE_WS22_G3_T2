/*
 * ContextSepBisLSEnde.cpp
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */

#include "ContextSepBisLSE1.h"

using namespace std;

ContextSepBisLSE1::ContextSepBisLSE1(ActionsSepBisLSE1 *shared_action, WsListen *werkstueckListen, Zeitmanager *zeitmanagerFSM,
		KonfigurationsdateiManager *konfigManager) :
		actions(shared_action), wsListen(werkstueckListen), zeitmanager(zeitmanagerFSM), konfig(konfigManager) {

	qnetHandler = new QnetHandler();
	attach = qnetHandler->openServer(S_SEP_BIS_LSENDE);

	actions->setupConnection();
	actions->setWsListen(wsListen);
	actions->setZeitmanager(zeitmanager);

	state = new WarteSepBisLSE1;
	state->setActions(actions);
	state->setWsListen(wsListen);
	state->setKonfig(konfig);
	state->setZeitmanager(zeitmanager);
	state->entry();
}

ContextSepBisLSE1::~ContextSepBisLSE1() {
	delete state;
}

void ContextSepBisLSE1::receiveSignal() {
	_pulse pulse;
	while (1) {

		int rcvid = MsgReceive(attach->chid, &pulse, sizeof(_pulse), NULL);

		if (rcvid == -1) { // Error occurred
			perror("[FSM_SepBisLSE1] MsgReceived failed");
		}
		if (rcvid == 0) { // Pulse was received
			switch (pulse.value.sival_int) {
			case LS_ENDE_AN:
				LsEAn();
				break;
			case WS_AUF_WEG_ZU_LSE:
				WsAufWegZuLSE();
				break;
			case FBM2_BEREIT:
				FBM2bereit();
				break;
			case ZEIT_UEBERGABE_AN_FBM2:
				WsWurdeUebergeben();
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
				cout << "[" << S_SEP_BIS_LSENDE << "]" << " received _IO_CONNECT via sync. message" << endl;
				MsgReply(rcvid, EOK, NULL, 0);
			}
		}
	}
}

void ContextSepBisLSE1::LsEAn(){
	state->LsEAn();
}

void ContextSepBisLSE1::WsAufWegZuLSE(){
	state->WsAufWegZuLSE();
}

void ContextSepBisLSE1::FBM2bereit(){
	state->FBM2bereit();
}

void ContextSepBisLSE1::WsWurdeUebergeben(){
	state->WsWurdeUebergeben();
}

void ContextSepBisLSE1::quittiert(){
	state->quittiert();
}

void ContextSepBisLSE1::keinFehler(){
	state->keinFehler();
}

void ContextSepBisLSE1::fehlerVerschwunden(){
	state->fehlerVerschwunden();
}

void ContextSepBisLSE1::eStop(){
	state->eStop();
}
