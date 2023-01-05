/*
 * Hoehenauswertung.cpp
 *
 *  Created on: 01.11.2022
 *      Author: User
 */

#include "Hoehenauswertung.h"

Hoehenauswertung::Hoehenauswertung(int ID, int dispID) {
	channelID = 0;
	clientID = ID;
	dispConID = ConnectAttach(0, 0, dispID, 0, 0);
	createChannel();
	gpio_bank_1 = mmap_device_io(0x1000, (uint64_t) 0x4804C000);
}

Hoehenauswertung::~Hoehenauswertung() {
	// TODO Auto-generated destructor stub
}

int Hoehenauswertung::getChannelID() {
	return channelID;
}

int Hoehenauswertung::createChannel() {
	int id = ChannelCreate(0);
	if (id < 0) {
		printf("Creating Channel in test Dispatcher failed!\n");
	}
	channelID = id;
	printf("Client %d: created channel with ID: %d\n", clientID, channelID);
	return id;
}

void Hoehenauswertung::sendTestPulses(int pulse) {
	printf("=======================SENDING TEST PULSE: %d =============================\n", pulse);
	MsgSendPulse(dispConID,-1,pulse,0);
}

void Hoehenauswertung::sendTestPulses(int pulse, uint32_t payload) {
	printf("=======================SENDING TEST PULSE: %d =============================\n", pulse);
	MsgSendPulse(dispConID,-1,pulse,payload);
}

void Hoehenauswertung::evaluateSomething() {
	struct _pulse pulse;

	int hochZaehler = 0;
	int flachZaehler = 0;
	int lochCounter = 0;
	int wsTyp = -1;

	while (true) {
		int rcvid = MsgReceivePulse(channelID, &pulse, sizeof(pulse), NULL);
		if (rcvid < 0) { // Error occurred
			printf("Client %d: MsgReceived failed\n", clientID);
			return;
		} else {

			// Beginn der WS Oberflaechen Erfassung
			int hoeheDif = 0;

//			if (pulse.value.sival_int > HOEHE_NICHTS) {
//				printf("kein WS Client %d: got pulse ID: %d, Payload: %d\n",clientID, pulse.code, pulse.value.sival_int);
//			}

			if(HOEHE_FLACHES_WS<pulse.value.sival_int&&pulse.value.sival_int<HOEHE_LOCH){

				//printf("cLoch: %d ", lochCounter);
				//printf("Loch WS Client %d: got pulse ID: %d, Payload: %d\n", clientID, pulse.code, pulse.value.sival_int);
				lochCounter++;

			}else if(HOEHE_HOEHES_WS<pulse.value.sival_int&&pulse.value.sival_int<HOEHE_FLACHES_WS){
//				printf("cLOW: %d ",flachZaehler);
//
//				printf("kleines WS Client %d: got pulse ID: %d, Payload: %d\n", clientID, pulse.code, pulse.value.sival_int);
				hoeheDif = HOEHE_NICHTS-pulse.value.sival_int;
				printf("hoehe: %d ", hoeheDif);
				flachZaehler++;

			}else if (pulse.value.sival_int<HOEHE_HOEHES_WS) {
//				printf("cHIGH: %d ",hochZaehler);
//				printf("HohesWS Client %d: got pulse ID: %d, Payload: %d\n", clientID, pulse.code, pulse.value.sival_int);

				hoeheDif = HOEHE_NICHTS-pulse.value.sival_int;
//				printf("hoehe: %d ", hoeheDif);
				hochZaehler++;
			}

			if(lochCounter>14&&hochZaehler>30){
				lochCounter=0;
				hochZaehler=0;
				wsTyp=HOCH_MIT_BOHRUNG;
			}else if (hochZaehler>50&&lochCounter==0) {
				hochZaehler=0;
				wsTyp=HOCH_OHNE_BOHRUNG;
			}else if(flachZaehler>50){
				flachZaehler=0;
				wsTyp=FLACH;
			}else{
				wsTyp=-1;
			}
		}

		// Gib den Typ aus
		if(wsTyp==0){
			printf("\nFLACH\n");
		}else if(wsTyp==1){
			printf("\nHOCH_OHNE\n");
		}else if(wsTyp==2){
			printf("\nHOCH_MIT\n");
		}else{

		}
	}
}
