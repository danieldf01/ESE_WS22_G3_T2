/*
 * WsAufWegZumHsLSAbisHS.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "WsAufWegZumHsLSAbisHS1.h"

void WsAufWegZumHsLSAbisHS1::entry(){

}

void WsAufWegZumHsLSAbisHS1::exit(){

}

void WsAufWegZumHsLSAbisHS1::WSinLSAbisHS(){

}

void WsAufWegZumHsLSAbisHS1::HSaktiv(){
	exit();
	// TODO Config
	if(zeitmanager->getTime() < (1800 + wsListen->ws_list_LSAnfang_bis_HS.front().getTimestamp())){
		new (this) FehlerWsZuFruehLSAbisHS1;
	} else{
		actions->WSinHS();
		if(wsListen->ws_list_LSAnfang_bis_HS.size() <= 0){
			new (this) WartenLSAbisHS1;
		}// else bleibe in diesem Zustand
	}
	entry();
}

void WsAufWegZumHsLSAbisHS1::quittiert(){

}

void WsAufWegZumHsLSAbisHS1::keinFehler(){

}

void WsAufWegZumHsLSAbisHS1::Fverschwunden(){
	exit();
	new (this) FehlerWsVerschwundenLSAbisHS1;
	entry();
}

void WsAufWegZumHsLSAbisHS1::eStop(){
	actions->eStop();
	new (this) WartenLSAbisHS1;
	entry();
}
