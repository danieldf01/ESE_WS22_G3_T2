/*
 * WarteAufRutscheFreiHSBisSep2.cpp
 *
 *  Created on: 19.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "WarteAufRutscheFreiHSBisSep2.h"

void WarteAufRutscheFreiHSBisSep2::entry() {
}

void WarteAufRutscheFreiHSBisSep2::exit() {
}

void WarteAufRutscheFreiHSBisSep2::WSinHSbisSep() {
}

void WarteAufRutscheFreiHSBisSep2::MetSenAn() {
}

void WarteAufRutscheFreiHSBisSep2::LSSepAn() {
}

void WarteAufRutscheFreiHSBisSep2::aussortieren1(){

}

void WarteAufRutscheFreiHSBisSep2::aussortieren2(){

}

void WarteAufRutscheFreiHSBisSep2::aussortieren3(){

}

void WarteAufRutscheFreiHSBisSep2::quittiert() {
}

void WarteAufRutscheFreiHSBisSep2::keinFehler() {
}

void WarteAufRutscheFreiHSBisSep2::fehlerCntDown() {
	if (!rutsche->rutsche2->rutscheVoll2) {
		if (!rutsche->rutsche2->rutscheVoll2) {
			actions->WsAussortieren();
			new (this) WSAufWegZumSep2;
		}else{
			actions->WsNichtAussortierbar();
		}
	}
}

void WarteAufRutscheFreiHSBisSep2::fehlerVerschwunden() {

}

void WarteAufRutscheFreiHSBisSep2::eStop() {
	exit();
	actions->eStop();
	new (this) WartenHSBisSep2;
	entry();
}
