/*
 * Warteaufentnehmen.cpp
 *
 *  Created on: 06.01.2023
 *      Author: tobi
 */

#include "WarteAufEntnehmenSepBisLSE2.h"

void WarteAufEntnehmenSepBisLSE2::entry() {
}

void WarteAufEntnehmenSepBisLSE2::exit() {
}

void WarteAufEntnehmenSepBisLSE2::LsEAn() {
}

void WarteAufEntnehmenSepBisLSE2::LsEAus() {
	actions->sendFBM2Bereit();
	new (this) WarteSepBisLSE2;
}

void WarteAufEntnehmenSepBisLSE2::WsPassieren() {
}

void WarteAufEntnehmenSepBisLSE2::WeicheSchliessen() {
}

void WarteAufEntnehmenSepBisLSE2::quittiert() {
}

void WarteAufEntnehmenSepBisLSE2::keinFehler() {
}

void WarteAufEntnehmenSepBisLSE2::fehlerVerschwunden() {
}

void WarteAufEntnehmenSepBisLSE2::eStop() {
	actions->eStop();
	new (this) WarteSepBisLSE2;
}
