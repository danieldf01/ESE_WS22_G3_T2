/*
 * QuittiertVerschwundenLSAbisHS.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "QuittiertVerschwundenLSAbisHS2.h"

void QuittiertVerschwundenLSAbisHS2::entry(){
	actions->fehlerRunter();
}

void QuittiertVerschwundenLSAbisHS2::exit(){

}

void QuittiertVerschwundenLSAbisHS2::WSinLSAbisHS(){

}

void QuittiertVerschwundenLSAbisHS2::HSaktiv(){

}

void QuittiertVerschwundenLSAbisHS2::quittiert(){

}

void QuittiertVerschwundenLSAbisHS2::keinFehler(){
	exit();
	if(wsListen->ws_list_LSAnfang_bis_HS.size() > 0){
		new (this) WsAufWegZumHsLSAbisHS2;
	} else{
		new (this) WartenLSAbisHS2;
	}
	entry();
}

void QuittiertVerschwundenLSAbisHS2::Fverschwunden(){

}

void QuittiertVerschwundenLSAbisHS2::eStop(){
	exit();
	actions->eStop();
	new (this) WartenLSAbisHS2;
	entry();
}
