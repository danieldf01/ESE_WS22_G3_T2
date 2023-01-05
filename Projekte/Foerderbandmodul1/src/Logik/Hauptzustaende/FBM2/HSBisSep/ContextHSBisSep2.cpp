/*
 * ContextHSBisSep2.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "ContextHSBisSep2.h"

ContextHSBisSep2::ContextHSBisSep2(ActionsHSBisSep2 *shared_action, WsListen *werkstueckListen, Zeitmanager *zeitmanagerFSM, Rutsche *r) :
actions(shared_action), wsListen(werkstueckListen), zeitmanager(zeitmanagerFSM), rutsche(r) {

	qnetHandler = new QnetHandler();
	attach = qnetHandler->openServer(S_HS_BIS_SEP2);

	actions->setupConnection();
	actions->setWsListen(wsListen);
	actions->setZeitmanager(zeitmanager);

	state = new WartenHSBisSep2();
	state->setActions(actions);
	state->setWsListen(wsListen);
	state->setZeitmanager(zeitmanager);
	state->setRutsche(rutsche);
	state->entry();

}

ContextHSBisSep2::~ContextHSBisSep2() {
	delete state;
}

void ContextHSBisSep2::receiveSignal() {
	_pulse pulse;
	while (1) {

		int rcvid = MsgReceive(attach->chid, &pulse, sizeof(_pulse), NULL);

		if (rcvid == -1) { // Error occurred
			perror("[FSM_HSbisSeperator2] MsgReceived failed");
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
				cout << "[" << S_HS_BIS_SEP1 << "]"
						<< " received _IO_CONNECT via sync. message" << endl;
				MsgReply(rcvid, EOK, NULL, 0);
			}
		}
	}
}

void ContextHSBisSep2::WSinHSbisSep() {
	state->WSinHSbisSep();
}

void ContextHSBisSep2::MetSenAn() {
	state->MetSenAn();
}

void ContextHSBisSep2::LSSepAn() {
	state->LSSepAn();
}

void ContextHSBisSep2::quittiert() {
	state->quittiert();
}

void ContextHSBisSep2::keinFehler() {
	state->keinFehler();
}

void ContextHSBisSep2::fehlerCntDown() {
	state->fehlerCntDown();
}

void ContextHSBisSep2::fehlerVerschwunden() {
	state->fehlerVerschwunden();
}

void ContextHSBisSep2::eStop() {
	state->eStop();
}
