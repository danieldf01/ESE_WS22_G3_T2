/*
 * QuittiertWSVerschwundenSepBisRut1.cpp
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */

#include "QuittiertWSVerschwundenSepBisRut1.h"

void QuittiertWSVerschwundenSepBisRut1::entry() {
	actions->fehlerRunter();
}

void QuittiertWSVerschwundenSepBisRut1::exit() {
}

void QuittiertWSVerschwundenSepBisRut1::LsRutAn() {
}

void QuittiertWSVerschwundenSepBisRut1::WsAussortieren() {
}

void QuittiertWSVerschwundenSepBisRut1::AuswerferEinfahren() {
}

void QuittiertWSVerschwundenSepBisRut1::quittiert() {
}

void QuittiertWSVerschwundenSepBisRut1::keinFehler() {
	exit();
	actions->schnellRunter();
	actions->zerstoereWsAussortieren();
	if (wsListen->ws_list_aussortieren.size() > 0) {
		if (konfig->get_value_of(Konfi_Codes::FBM1_AUSWERFER_TRUE)) { // Es ist ein Auswerfer TODO Auswerfer als Konfi Code anlegen
			actions->seperatorAn();
			new (this) AuswerferAusgefahrenSepBisRut1;
		} else { // Es ist eine Weiche
			new (this) AuswerferEingefahrenSepBisRut1;
		}
	} else if (wsListen->ws_list_aussortieren.size() <= 0) {
		new (this) WarteSepBisRut1;
	}
	entry();
}

void QuittiertWSVerschwundenSepBisRut1::Fverschwunden() {
}

void QuittiertWSVerschwundenSepBisRut1::eStop() {
	new (this) WarteSepBisRut1;
}
