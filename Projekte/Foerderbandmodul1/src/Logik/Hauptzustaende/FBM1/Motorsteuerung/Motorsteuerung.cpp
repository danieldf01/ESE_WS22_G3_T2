/*
 * Motorsteuerung.cpp
 *
 *  Created on: 12.12.2022
 *      Author: acy003
 */

#include "Motorsteuerung.h"

Motorsteuerung::Motorsteuerung(Zeitmanager *fbm1, Zeitmanager *fbm2) {
	qnetHandler = new QnetHandler();
	attach = qnetHandler->openServer(S_MOTORSTEUERUNG);
	stateM1 = new Motor(fbm1, fbm2);
	stateM2 = new Motor(fbm1, fbm2);
	stateM1->zeitFBM1= fbm1;
	stateM2->zeitFBM2= fbm2;
}

Motorsteuerung::~Motorsteuerung() {
	qnetHandler->~QnetHandler();
	stateM1->~Motor();
	stateM2->~Motor();
}

void Motorsteuerung::receiveSignal(){
	_pulse pulse;
		while (1) {

			int rcvid = MsgReceive(attach->chid, &pulse, sizeof(_pulse), NULL);

			if (rcvid == -1) { // Error occurred
				perror("[FSM_LSAnfang] MsgReceived failed");
			}
			if (rcvid == 0) { // Pulse was received
				if(pulse.code== _PULSE_CODE_MINAVAIL+1){
					stateM1->handlePulse(1,pulse.value.sival_int);
				}
				else{

					stateM2->handlePulse(2,pulse.value.sival_int);
				}
			}
			// some sync msg was received
			if ((_IO_BASE <= pulse.type) && (pulse.type <= _IO_MAX)) {
				if (pulse.type == _IO_CONNECT) {

					MsgReply(rcvid, EOK, NULL, 0);
					stateM1->logikID=qnetHandler->connectServer(LOGIK);
					stateM2->logikID = stateM1->logikID;
				}
			}
		}
}
