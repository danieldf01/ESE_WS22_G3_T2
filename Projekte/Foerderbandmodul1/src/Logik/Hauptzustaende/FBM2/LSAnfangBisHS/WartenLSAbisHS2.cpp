/*
 * WartenLSAbisHS.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "WartenLSAbisHS2.h"

void WartenLSAbisHS2::entry(){

}

void WartenLSAbisHS2::exit(){

}

void WartenLSAbisHS2::WSinLSAbisHS(){
	if(wsListen->ws_list_LSAnfang_bis_HS.size() > 0){
		exit();
		new (this) WsAufWegZumHsLSAbisHS2;
		entry();
	}
}

void WartenLSAbisHS2::HSaktiv(){
	exit();
	new (this) FehlerWsZuVielLSAbisHS2;
	entry();
}

void WartenLSAbisHS2::quittiert(){

}

void WartenLSAbisHS2::keinFehler(){

}

void WartenLSAbisHS2::Fverschwunden(){

}

void WartenLSAbisHS2::eStop(){
	actions->eStop();
}
