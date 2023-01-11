/*
 * AuswerferAusgefahrenSepBisRut1.cpp
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */

#include "AuswerferAusgefahrenSepBisRut1.h"

void AuswerferAusgefahrenSepBisRut1::entry() {
}

void AuswerferAusgefahrenSepBisRut1::exit() {
}

void AuswerferAusgefahrenSepBisRut1::LsRutAn() {
	actions->seperatorAus();
	actions->deleteTimerVerschwunden();
	actions->schnellRunter();
	actions->zerstoereWsAussortieren();
	if(wsListen->ws_list_aussortieren.size()>0){
		if (konfig->get_value_of(Konfi_Codes::FBM1_AUSWERFER_TRUE)) { // Es ist ein Auswerfer TODO Auswerfer als Konfi Code anlegen
			actions->seperatorAn();
			new (this) AuswerferAusgefahrenSepBisRut1;
		} else { // Es ist eine Weiche
			//wir sind schon im richtigen State
		}
	}else if(wsListen->ws_list_aussortieren.size()<=0){
		new (this) WarteSepBisRut1;
	}
}

void AuswerferAusgefahrenSepBisRut1::WsAussortieren() {
}

void AuswerferAusgefahrenSepBisRut1::AuswerferEinfahren() {
	actions->seperatorAus();
	new (this) AuswerferEingefahrenSepBisRut1;
}

void AuswerferAusgefahrenSepBisRut1::quittiert() {
}

void AuswerferAusgefahrenSepBisRut1::keinFehler() {
}

void AuswerferAusgefahrenSepBisRut1::Fverschwunden() {
}

void AuswerferAusgefahrenSepBisRut1::eStop() {
	new (this) WarteSepBisRut1;
}
