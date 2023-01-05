/*
 * WartenHSBisSep1.cpp
 *
 *  Created on: 17.12.2022
 *      Author: tobias
 */

#include "WartenHSBisSep1.h"

void WartenHSBisSep1::entry() {
}

void WartenHSBisSep1::exit() {
}

void WartenHSBisSep1::WSinHSbisSep() {
	if(wsListen->ws_list_HS_bis_Seperator.size() > 0){
		exit();
		new (this) WSAufWegZumSep1;
		entry();
	}
}

void WartenHSBisSep1::MetSenAn() {

}

void WartenHSBisSep1::LSSepAn() {
	exit();
	new (this) FehlerWSZuVielHSBisSep1;
	entry();
}

void WartenHSBisSep1::aussortieren1(){

}

void WartenHSBisSep1::aussortieren2(){

}

void WartenHSBisSep1::aussortieren3(){

}

void WartenHSBisSep1::aussortieren4(){

}

void WartenHSBisSep1::quittiert() {
}

void WartenHSBisSep1::keinFehler() {
}

void WartenHSBisSep1::fehlerCntDown(){

}

void WartenHSBisSep1::fehlerVerschwunden(){

}

void WartenHSBisSep1::eStop() {
	actions->eStop();
}
