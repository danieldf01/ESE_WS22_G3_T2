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
	cout << "AuswerferEingefahrenSepBisRut2 recv:LsRutAn" << endl;
	exit();
	//actions->deleteTimerVerschwunden();
	actions->schnellRunter();
	actions->zerstoereWsAussortieren();
	actions->sendFBM2Bereit();
	new (this) WarteSepBisRut2;
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
