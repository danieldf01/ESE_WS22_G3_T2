/*
 * WsAufWegZumHsLSAbisHS.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "WsAufWegZumHsLSAbisHS2.h"

void WsAufWegZumHsLSAbisHS2::entry(){

}

void WsAufWegZumHsLSAbisHS2::exit(){

}

void WsAufWegZumHsLSAbisHS2::WSinLSAbisHS(){

}

void WsAufWegZumHsLSAbisHS2::HSaktiv(){
//	cout << "[FBM2] Zustand: WsAufWegZumHsLSAbisHS2 recv: HSaktiv" << endl;
	cout << "ZEIT: " << zeitmanager->getTime() << ", WS TIMESTAMP: " << wsListen->ws_ls_anfang_bis_hs_2->getTimestamp() << endl;
	//TODO Zeitwerte ueber Konfig Datei
	if(zeitmanager->getTime() < (1800 + wsListen->ws_ls_anfang_bis_hs_2->getTimestamp())){
		new (this) FehlerWsZuFruehLSAbisHS2;
	} else{
		actions->WSinHS();
		new (this) WartenLSAbisHS2;
	}
	entry();
}

void WsAufWegZumHsLSAbisHS2::quittiert(){

}

void WsAufWegZumHsLSAbisHS2::keinFehler(){

}

void WsAufWegZumHsLSAbisHS2::Fverschwunden(){
	new (this) FehlerWsVerschwundenLSAbisHS2;
	entry();
}

void WsAufWegZumHsLSAbisHS2::eStop(){
	actions->eStop();
	new (this) WartenLSAbisHS2;
}
