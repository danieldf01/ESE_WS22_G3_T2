/*
 * WartenLSAbisHS.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "WartenLSAbisHS1.h"

void WartenLSAbisHS1::entry(){

}

void WartenLSAbisHS1::exit(){

}

void WartenLSAbisHS1::WSinLSAbisHS(){
	if(wsListen->ws_list_LSAnfang_bis_HS.size() > 0){
		exit();
		new (this) WsAufWegZumHsLSAbisHS1;
		entry();
	}
}

void WartenLSAbisHS1::HSaktiv(){
	exit();
	new (this) FehlerWsZuVielLSAbisHS1;
	entry();
}

void WartenLSAbisHS1::quittiert(){

}

void WartenLSAbisHS1::keinFehler(){

}

void WartenLSAbisHS1::Fverschwunden(){

}

void WartenLSAbisHS1::eStop(){
	actions->eStop();
}
