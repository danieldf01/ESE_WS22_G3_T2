/*
 * WarteSepBisRut2.cpp
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */
#include "WarteSepBisRut2.h"

void WarteSepBisRut2::entry() {
}

void WarteSepBisRut2::exit() {
}

void WarteSepBisRut2::LsRutAn() {
	new (this) FehlerWSZuVielSepBisRut2;
	entry();
}

void WarteSepBisRut2::WsAussortieren() {
	exit();
	if (konfig->get_value_of(Konfi_Codes::FBM2_AUSWERFER_TRUE)) { // Es ist ein Auswerfer TODO Auswerfer als Konfi Code anlegen
		actions->seperatorAn();
		new (this) AuswerferAusgefahrenSepBisRut2;
	} else { // Es ist eine Weiche
		new (this) AuswerferEingefahrenSepBisRut2;
	}
}

void WarteSepBisRut2::AuswerferEinfahren() {
}

void WarteSepBisRut2::quittiert() {
}

void WarteSepBisRut2::keinFehler() {
}

void WarteSepBisRut2::Fverschwunden() {
}

void WarteSepBisRut2::eStop() {
}
