/*
 * ContextHSBisSep1.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "ContextHSBisSep1.h"

ContextHSBisSep1::ContextHSBisSep1(ActionsHSBisSep1 *shared_action, WsListen *werkstueckListen, Zeitmanager *zeitmanagerFSM, Rutsche *r) :
		actions(shared_action), wsListen(werkstueckListen), zeitmanager(zeitmanagerFSM), rutsche(r) {

	qnetHandler = new QnetHandler();
	attach = qnetHandler->openServer(S_HS_BIS_SEP1);

	actions->setupConnection();
	actions->setWsListen(wsListen);
	actions->setZeitmanager(zeitmanager);

	state = new WartenHSBisSep1();
	state->setActions(actions);
	state->setWsListen(wsListen);
	state->setZeitmanager(zeitmanager);
	state->setRutsche(rutsche);
	state->entry();

}

ContextHSBisSep1::~ContextHSBisSep1() {
	delete state;
}

void ContextHSBisSep1::receiveSignal() {
	_pulse pulse;
	while (1) {

		int rcvid = MsgReceive(attach->chid, &pulse, sizeof(_pulse), NULL);

		if (rcvid == -1) { // Error occurred
			perror("[FSM_HSbisSeperator] MsgReceived failed");
		}
		if (rcvid == 0) { // Pulse was received
			switch (pulse.value.sival_int) {
			case WS_IN_HS_BIS_SEPERATOR:
				WSinHSbisSep();
				break;
			case METALLSENSOR_AN:
				MetSenAn();
				break;
			case LS_SEPERATOR_AN:
				LSSepAn();
				break;
			case QUITTIERT:
				quittiert();
				break;
			case KEIN_FEHLER:
				keinFehler();
				break;
			case FEHLER_RUNTER:
				fehlerCntDown();
				break;
			case FEHLER_WS_VERSCHWUNDEN_HS_BIS_SEP:
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
				cout << "[" << S_HS_BIS_SEP1 << "]" << " received _IO_CONNECT via sync. message" << endl;
				MsgReply(rcvid, EOK, NULL, 0);
			}
		}
	}
}

void ContextHSBisSep1::WSinHSbisSep() {
	state->WSinHSbisSep();
}

void ContextHSBisSep1::MetSenAn() {
	state->MetSenAn();
}

void ContextHSBisSep1::LSSepAn() {
	state->LSSepAn();
}

void ContextHSBisSep1::quittiert() {
	state->quittiert();
}

void ContextHSBisSep1::keinFehler() {
	state->keinFehler();
}

void ContextHSBisSep1::fehlerCntDown() {
	state->fehlerCntDown();
}

void ContextHSBisSep1::fehlerVerschwunden() {
	state->fehlerVerschwunden();
}

void ContextHSBisSep1::eStop() {
	state->eStop();
}
