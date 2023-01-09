/*
 * WsAufWegZuLSEndeSepBisLSE2.cpp
 *
 *  Created on: 22.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "WsAufWegZuLSEndeSepBisLSE2.h"

using namespace std;

void WsAufWegZuLSEndeSepBisLSE2::entry(){

}

void WsAufWegZuLSEndeSepBisLSE2::exit(){

}

void WsAufWegZuLSEndeSepBisLSE2::LsEAn(){
//	cout << "WsAufWegZuLSEndeSepBisLSE2 Recv: LsEAn" <<endl;
	exit();
	actions->deleteTimerVerschwunden();
	//WS zu frueh angekommen?
	if(zeitmanager->getTime() < (1500 + wsListen->ws_passieren_2->getTimestamp())){
		new (this) FehlerWSZuFruehSepBisLSE2;
	} else{

		Werkstueck ws = *wsListen->ws_passieren_2;
		int wsId = ws.getiD();
		int wsTyp = ws.getWsTyp();
		double wsMeanhight = ws.getMittlereHoehe();
		double wsHeight = ws.getHoehenmesswert();

		// Konsolen Ausgabe
		cout << "----Werkstueck Daten----" << endl;
		cout << "wsId" << wsId << endl;
		cout << "wsTyp" << wsTyp << endl;
		printf("wsMeanhight %f", wsMeanhight);
		printf("wsHeight %f", wsHeight);

		// MQTT Stuff
		std::string address ="tcp://192.168.101.201:1883";
		std::string clientID="FESTO_Client_Pub";
		std::string topic="werkstueck";

		MQTTClientHandler *client = new MQTTClientHandler(address, clientID);
		client->senden(topic, 8000, "DÜNN", 2.0, 2666.9567);
		client->destroy();

		actions->schnellRunter();
		new (this) WarteAufEntnehmenSepBisLSE2;
	}
	entry();
}

void WsAufWegZuLSEndeSepBisLSE2::LsEAus() {
}

void WsAufWegZuLSEndeSepBisLSE2::WsPassieren(){

}

void WsAufWegZuLSEndeSepBisLSE2::WeicheSchliessen(){

}

void WsAufWegZuLSEndeSepBisLSE2::quittiert(){

}

void WsAufWegZuLSEndeSepBisLSE2::keinFehler(){

}

void WsAufWegZuLSEndeSepBisLSE2::fehlerVerschwunden(){
	exit();
	new (this) FehlerWSVerschwundenSepBisLSE2;
	entry();
}

void WsAufWegZuLSEndeSepBisLSE2::eStop(){
	actions->eStop();
	new (this) WarteSepBisLSE2;
}
