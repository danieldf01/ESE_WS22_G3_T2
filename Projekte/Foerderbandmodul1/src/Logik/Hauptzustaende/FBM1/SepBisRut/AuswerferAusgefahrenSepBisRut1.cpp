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
