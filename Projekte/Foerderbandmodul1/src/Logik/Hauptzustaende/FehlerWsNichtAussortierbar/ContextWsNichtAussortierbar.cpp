/*
 * ContextWsNichtAussortierbar.cpp
 *
 *  Created on: 21.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "ContextWsNichtAussortierbar.h"

using namespace std;

ContextWsNichtAussortierbar::ContextWsNichtAussortierbar(ActionsWsNichtAussortierbar *shared_action, Rutsche *r) :
		actions(shared_action), rutsche(r) {

	qnetHandler = new QnetHandler();
	attach = qnetHandler->openServer(S_F_WS_NICHT_AUSSORTIERBAR);
	chID = attach->chid;
	actions->setupConnection();

	state = new WartenWsNichtAussortierbar();
	state->setActions(actions);
	state->setRutsche(rutsche);
	state->entry();
}

ContextWsNichtAussortierbar::~ContextWsNichtAussortierbar() {
	delete state;
}

void ContextWsNichtAussortierbar::receiveSignal() {
	_pulse pulse;
	while (1) {

		int rcvid = MsgReceive(attach->chid, &pulse, sizeof(_pulse), NULL);

		if (rcvid == -1) { // Error occurred
			perror("[FSM_WsNichtAussortierbar] MsgReceived failed");
		}
		if (rcvid == 0) { // Pulse was received
			switch (pulse.code) {

			case CODE_FBM_1:	//pulse von FBM1
				switch (pulse.value.sival_int) {
				case LS_RUTSCHE_AUS:
					LsRutscheAus1();
					break;
				case WS_NICHT_AUSSORTIERBAR:
					WsNichtAussortierbar();
					break;
				case E_STOP_AN:
					eStop();
					break;
				}
				break;

			case CODE_FBM_2:	//pulse von FBM2
				switch (pulse.value.sival_int) {
				case LS_RUTSCHE_AUS:
					LsRutscheAus2();
					break;
				case WS_NICHT_AUSSORTIERBAR:
					WsNichtAussortierbar();
					break;
				case E_STOP_AN:
					eStop();
					break;
				}
			}
			// handle name_open calls for this server
			if ((_IO_BASE <= pulse.type) && (pulse.type <= _IO_MAX)) {
				if (pulse.type == _IO_CONNECT) {
					cout << "[" << S_F_WS_NICHT_AUSSORTIERBAR << "]"
							<< " received _IO_CONNECT via sync. message"
							<< endl;
					MsgReply(rcvid, EOK, NULL, 0);
				}
			}
		}
	}
}

void ContextWsNichtAussortierbar::LsRutscheAus1(){
	state->LsRutscheAus1();
}

void ContextWsNichtAussortierbar::LsRutscheAus2(){
	state->LsRutscheAus2();
}

void ContextWsNichtAussortierbar::WsNichtAussortierbar(){
	state->WsNichtAussortierbar();
}

void ContextWsNichtAussortierbar::eStop(){
	state->eStop();
}
