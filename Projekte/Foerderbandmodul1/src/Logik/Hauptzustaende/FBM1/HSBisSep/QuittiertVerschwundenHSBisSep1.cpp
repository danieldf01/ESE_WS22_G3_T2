/*
 * QuittiertVerschwundenHSBisSep1.cpp
 *
 *  Created on: 19.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "QuittiertVerschwundenHSBisSep1.h"

void QuittiertVerschwundenHSBisSep1::entry() {
	actions->fehlerRunter();
}

void QuittiertVerschwundenHSBisSep1::exit() {
}

void QuittiertVerschwundenHSBisSep1::WSinHSbisSep() {
}

void QuittiertVerschwundenHSBisSep1::MetSenAn() {
}

void QuittiertVerschwundenHSBisSep1::LSSepAn() {
}

void QuittiertVerschwundenHSBisSep1::aussortieren1(){

}

void QuittiertVerschwundenHSBisSep1::aussortieren2(){

}

void QuittiertVerschwundenHSBisSep1::aussortieren3(){

}

void QuittiertVerschwundenHSBisSep1::aussortieren4(){

}

void QuittiertVerschwundenHSBisSep1::quittiert() {
}

void QuittiertVerschwundenHSBisSep1::keinFehler() {
	exit();
	if(wsListen->ws_list_HS_bis_Seperator.size() > 0){
		new (this) WSAufWegZumSep1;
	} else{
		new (this) WartenHSBisSep1;
	}
	entry();
}

void QuittiertVerschwundenHSBisSep1::fehlerCntDown(){

}

void QuittiertVerschwundenHSBisSep1::fehlerVerschwunden(){

}

void QuittiertVerschwundenHSBisSep1::eStop() {
	exit();
	actions->eStop();
	new (this) WartenHSBisSep1;
	entry();
}
