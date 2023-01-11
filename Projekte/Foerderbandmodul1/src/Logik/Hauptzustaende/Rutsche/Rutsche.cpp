/*
 * Rutsche.cpp
 *
 *  Created on: 15.12.2022
 *      Author: acy003
 */

#include "Rutsche.h"

Rutsche::Rutsche() {

	qnetHandler = new QnetHandler();
	attach = qnetHandler->openServer(S_RUTSCHE);
	rutsche1= new RutschenSteuerung();
	rutsche2= new RutschenSteuerung();
}

Rutsche::~Rutsche() {
	// TODO Auto-generated destructor stub
}

void Rutsche::receiveSignal(){
	_pulse pulse;
		while (1) {

			int rcvid = MsgReceive(attach->chid, &pulse, sizeof(_pulse), NULL);

			if (rcvid == -1) { // Error occurred
				perror("[FSM_LSAnfang] MsgReceived failed");
			}
			if (rcvid == 0) { // Pulse was received
				if(pulse.code== CODE_FBM_1){
					rutsche1->handlePulse(1,pulse.value.sival_int);
				}
				else{

					rutsche2->handlePulse(2,pulse.value.sival_int);
				}
			}
			// some sync msg was received
			if ((_IO_BASE <= pulse.type) && (pulse.type <= _IO_MAX)) {
				if (pulse.type == _IO_CONNECT) {

					MsgReply(rcvid, EOK, NULL, 0);
					rutsche1->logikID=qnetHandler->connectServer(LOGIK);
					rutsche2->logikID = rutsche1->logikID;
				}
			}
		}
}
