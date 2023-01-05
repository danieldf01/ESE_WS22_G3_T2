/*
 * QuittiertVerschwundenHSBisSep2.cpp
 *
 *  Created on: 19.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "QuittiertVerschwundenHSBisSep2.h"

void QuittiertVerschwundenHSBisSep2::entry() {
	actions->fehlerRunter();
}

void QuittiertVerschwundenHSBisSep2::exit() {
}

void QuittiertVerschwundenHSBisSep2::WSinHSbisSep() {
}

void QuittiertVerschwundenHSBisSep2::MetSenAn() {
}

void QuittiertVerschwundenHSBisSep2::LSSepAn() {
}

void QuittiertVerschwundenHSBisSep2::aussortieren1(){

}

void QuittiertVerschwundenHSBisSep2::aussortieren2(){

}

void QuittiertVerschwundenHSBisSep2::aussortieren3(){

}

void QuittiertVerschwundenHSBisSep2::quittiert() {
}

void QuittiertVerschwundenHSBisSep2::keinFehler() {
	exit();
	if(wsListen->ws_list_HS_bis_Seperator.size() > 0){
		new (this) WSAufWegZumSep2;
	} else{
		new (this) WartenHSBisSep2;
	}
	entry();
}

void QuittiertVerschwundenHSBisSep2::fehlerCntDown(){

}

void QuittiertVerschwundenHSBisSep2::fehlerVerschwunden(){

}

void QuittiertVerschwundenHSBisSep2::eStop() {
	exit();
	actions->eStop();
	new (this) WartenHSBisSep2;
	entry();
}
