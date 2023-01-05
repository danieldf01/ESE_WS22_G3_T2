/*
 * AuswerferEingefahrenSepBisRut2.cpp
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */

#include "AuswerferEingefahrenSepBisRut2.h"

using namespace std;

void AuswerferEingefahrenSepBisRut2::entry() {
}

void AuswerferEingefahrenSepBisRut2::exit() {
}

void AuswerferEingefahrenSepBisRut2::LsRutAn() {
	cout << "in state" << endl;
	exit();
	actions->deleteTimerVerschwunden();
	actions->schnellRunter();
	actions->zerstoereWsAussortieren();
//	if(wsListen->ws_list_aussortieren_2.size()>0){
//		if (konfig->get_value_of(Konfi_Codes::FBM2_AUSWERFER_TRUE)) { // Es ist ein Auswerfer TODO Auswerfer als Konfi Code anlegen
//			actions->seperatorAn();
//			new (this) AuswerferAusgefahrenSepBisRut2;
//		} else { // Es ist eine Weiche
//			//wir sind schon im richtigen State
//		}
//	}else if(wsListen->ws_list_aussortieren_2.size()<=0){
//		new (this) WarteSepBisRut2;
//	}
	entry();
}

void AuswerferEingefahrenSepBisRut2::WsAussortieren() {
}

void AuswerferEingefahrenSepBisRut2::AuswerferEinfahren() {
}

void AuswerferEingefahrenSepBisRut2::quittiert() {
}

void AuswerferEingefahrenSepBisRut2::keinFehler() {
}

void AuswerferEingefahrenSepBisRut2::Fverschwunden() {
	new (this) FehlerWSVerschwundenSepBisRut2;
	entry();
}

void AuswerferEingefahrenSepBisRut2::eStop() {
}
