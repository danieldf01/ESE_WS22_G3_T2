/*
 * ContextPassieren.cpp
 *
 *  Created on: 07.01.2023
 *      Author: Daniel Drefs Fernandes
 */

#include "ContextPassieren.h"

using namespace std;

ContextPassieren::ContextPassieren(ActionsPassieren *shared_action, WsListen *werkstueckListen,
		KonfigurationsdateiManager *konfigManager) :
		actions(shared_action), wsListen(werkstueckListen), konfig(konfigManager) {

	qnetHandler = new QnetHandler();
	attach = qnetHandler->openServer(S_PASSIEREN);

	actions->setupConnection();
	actions->setWsListen(wsListen);

	state = new WartenPassieren;
	state->setActions(actions);
	state->setWsListen(wsListen);
	state->setKonfig(konfig);
	state->entry();
}

ContextPassieren::~ContextPassieren() {
	delete state;
}

void ContextPassieren::receiveSignal(){
	_pulse pulse;
	while (1) {

		int rcvid = MsgReceive(attach->chid, &pulse, sizeof(_pulse), NULL);

		if (rcvid == -1) { // Error occurred
			perror("[FSM_Passieren] MsgReceived failed");
		}
		if (rcvid == 0) { // Pulse was received
			switch (pulse.value.sival_int) {
			case WS_PASSIEREN:
				WsPassieren();
				break;
			case ZEIT_WEICHE:
				WeicheSchliessen();
				break;
			case E_STOP_AN:
				eStop();
				break;
			}
		}
		// handle name_open calls for this server
		if ((_IO_BASE <= pulse.type) && (pulse.type <= _IO_MAX)) {
			if (pulse.type == _IO_CONNECT) {
				cout << "[" << S_PASSIEREN << "]" << " received _IO_CONNECT via sync. message" << endl;
				MsgReply(rcvid, EOK, NULL, 0);
			}
		}
	}
}

void ContextPassieren::WsPassieren(){
	state->WsPassieren();
}

void ContextPassieren::WeicheSchliessen(){
	state->WeicheSchliessen();
}

void ContextPassieren::eStop(){
	state->eStop();
}
