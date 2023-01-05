/*
 * AuswerferEingefahrenSepBisRut1.cpp
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */

#include "AuswerferEingefahrenSepBisRut1.h"

using namespace std;

void AuswerferEingefahrenSepBisRut1::entry() {
}

void AuswerferEingefahrenSepBisRut1::exit() {
}

void AuswerferEingefahrenSepBisRut1::LsRutAn() {
	cout << "in state" << endl;
	exit();
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
	entry();
}

void AuswerferEingefahrenSepBisRut1::WsAussortieren() {
}

void AuswerferEingefahrenSepBisRut1::AuswerferEinfahren() {
}

void AuswerferEingefahrenSepBisRut1::quittiert() {
}

void AuswerferEingefahrenSepBisRut1::keinFehler() {
}

void AuswerferEingefahrenSepBisRut1::Fverschwunden() {
	new (this) FehlerWSVerschwundenSepBisRut1;
	entry();
}

void AuswerferEingefahrenSepBisRut1::eStop() {
}
