/*
 * QuittiertVerschwundenLSAbisHS.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "QuittiertVerschwundenLSAbisHS1.h"

void QuittiertVerschwundenLSAbisHS1::entry(){
	actions->fehlerRunter();
}

void QuittiertVerschwundenLSAbisHS1::exit(){

}

void QuittiertVerschwundenLSAbisHS1::WSinLSAbisHS(){

}

void QuittiertVerschwundenLSAbisHS1::HSaktiv(){

}

void QuittiertVerschwundenLSAbisHS1::quittiert(){

}

void QuittiertVerschwundenLSAbisHS1::keinFehler(){
	exit();
	if(wsListen->ws_list_LSAnfang_bis_HS.size() > 0){
		new (this) WsAufWegZumHsLSAbisHS1;
	} else{
		new (this) WartenLSAbisHS1;
	}
	entry();
}

void QuittiertVerschwundenLSAbisHS1::Fverschwunden(){

}

void QuittiertVerschwundenLSAbisHS1::eStop(){
	exit();
	actions->eStop();
	new (this) WartenLSAbisHS1;
	entry();
}
