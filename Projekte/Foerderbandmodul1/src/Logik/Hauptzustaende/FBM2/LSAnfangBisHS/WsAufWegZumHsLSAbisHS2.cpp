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
	exit();
//	if(zeitmanager->getTime() < (1800 + wsListen->ws_list_LSAnfang_bis_HS_2.front().getTimestamp())){
//		new (this) FehlerWsZuFruehLSAbisHS2;
//	} else{
//		actions->WSinHS();
//		if(wsListen->ws_list_LSAnfang_bis_HS_2.size() <= 0){
//			new (this) WartenLSAbisHS2;
//		}
//	}
	entry();
}

void WsAufWegZumHsLSAbisHS2::quittiert(){

}

void WsAufWegZumHsLSAbisHS2::keinFehler(){

}

void WsAufWegZumHsLSAbisHS2::Fverschwunden(){
	exit();
	new (this) FehlerWsVerschwundenLSAbisHS2;
	entry();
}

void WsAufWegZumHsLSAbisHS2::eStop(){
	exit();
	actions->eStop();
	new (this) WartenLSAbisHS2;
	entry();
}
