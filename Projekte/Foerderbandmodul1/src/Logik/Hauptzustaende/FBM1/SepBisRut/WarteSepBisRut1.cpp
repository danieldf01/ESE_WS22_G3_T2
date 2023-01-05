/*
 * WarteSepBisRut1.cpp
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */
// TODO MISSING STUFF!
#include "WarteSepBisRut1.h"

void WarteSepBisRut1::entry() {
}

void WarteSepBisRut1::exit() {
}

void WarteSepBisRut1::LsRutAn() {
	exit();
	new (this) FehlerWSZuVielSepBisRut1;
	entry();
}

void WarteSepBisRut1::WsAussortieren() {
	if(wsListen->ws_list_aussortieren.size()>0){
		exit();
		if (konfig->get_value_of(Konfi_Codes::FBM1_AUSWERFER_TRUE)) { // Es ist ein Auswerfer TODO Auswerfer als Konfi Code anlegen
			actions->seperatorAn();
			new (this) AuswerferAusgefahrenSepBisRut1;
		} else { // Es ist eine Weiche
			new (this) AuswerferEingefahrenSepBisRut1;
		}
		entry();
	}
}

void WarteSepBisRut1::AuswerferEinfahren() {
}

void WarteSepBisRut1::quittiert() {
}

void WarteSepBisRut1::keinFehler() {
}

void WarteSepBisRut1::Fverschwunden() {
}

void WarteSepBisRut1::eStop() {
}
