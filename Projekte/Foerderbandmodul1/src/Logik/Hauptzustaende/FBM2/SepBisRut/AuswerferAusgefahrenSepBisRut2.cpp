/*
 * AuswerferAusgefahrenSepBisRut2.cpp
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */

#include "AuswerferAusgefahrenSepBisRut2.h"

void AuswerferAusgefahrenSepBisRut2::entry() {
}

void AuswerferAusgefahrenSepBisRut2::exit() {
}

void AuswerferAusgefahrenSepBisRut2::LsRutAn() {
		actions->seperatorAus();
		actions->deleteTimerVerschwunden();
		actions->schnellRunter();
		actions->zerstoereWsAussortieren();
		actions->sendFBM2Bereit();
		new (this) WarteSepBisRut2;
}

void AuswerferAusgefahrenSepBisRut2::WsAussortieren() {
}

void AuswerferAusgefahrenSepBisRut2::AuswerferEinfahren() {
	actions->seperatorAus();
	new (this) AuswerferEingefahrenSepBisRut2;
}

void AuswerferAusgefahrenSepBisRut2::quittiert() {
}

void AuswerferAusgefahrenSepBisRut2::keinFehler() {
}

void AuswerferAusgefahrenSepBisRut2::Fverschwunden() {
}

void AuswerferAusgefahrenSepBisRut2::eStop() {
	new (this) WarteSepBisRut2;
}
