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
	cout << "WsAufWegZuLSEndeSepBisLSE2 Recv: LsEAn" <<endl;
	exit();
	actions->deleteTimerVerschwunden();
	//WS zu frueh angekommen?
	if(zeitmanager->getTime() < (1500 + wsListen->ws_passieren_2->getTimestamp())){
		new (this) FehlerWSZuFruehSepBisLSE2;
	} else{
		// TODO MQTT missing
		cout << "TODO Send per MQTT here WsAufWegZuLSEndeSepBisLSE2" << endl;
		cout << "TODO Konsolenausgabe" << endl;
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

void WsAufWegZuLSEndeSepBisLSE2::FBM2bereit(){

}

void WsAufWegZuLSEndeSepBisLSE2::WsWurdeUebergeben(){

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
