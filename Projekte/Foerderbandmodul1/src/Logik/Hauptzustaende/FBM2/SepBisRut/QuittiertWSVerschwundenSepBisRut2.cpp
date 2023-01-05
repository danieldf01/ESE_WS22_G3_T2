/*
 * QuittiertWSVerschwundenSepBisRut2.cpp
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */

#include "QuittiertWSVerschwundenSepBisRut2.h"

void QuittiertWSVerschwundenSepBisRut2::entry() {
	actions->fehlerRunter();
}

void QuittiertWSVerschwundenSepBisRut2::exit() {
}

void QuittiertWSVerschwundenSepBisRut2::LsRutAn() {
}

void QuittiertWSVerschwundenSepBisRut2::WsAussortieren() {
}

void QuittiertWSVerschwundenSepBisRut2::AuswerferEinfahren() {
}

void QuittiertWSVerschwundenSepBisRut2::quittiert() {
}

void QuittiertWSVerschwundenSepBisRut2::keinFehler() {
	exit();
	actions->schnellRunter();
	actions->zerstoereWsAussortieren();
//	if (wsListen->ws_list_aussortieren_2.size() > 0) {
//		if (konfig->get_value_of(Konfi_Codes::FBM2_AUSWERFER_TRUE)) { // Es ist ein Auswerfer TODO Auswerfer als Konfi Code anlegen
//			actions->seperatorAn();
//			new (this) AuswerferAusgefahrenSepBisRut2;
//		} else { // Es ist eine Weiche
//			new (this) AuswerferEingefahrenSepBisRut2;
//		}
//	} else if (wsListen->ws_list_aussortieren.size() <= 0) {
//		new (this) WarteSepBisRut2;
//	}
	entry();
}

void QuittiertWSVerschwundenSepBisRut2::Fverschwunden() {
}

void QuittiertWSVerschwundenSepBisRut2::eStop() {
}
