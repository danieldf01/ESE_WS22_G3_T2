/*
 * FehlerWSZuVielSepBisRut2.cpp
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */
 // TODO DONE
#include "FehlerWSZuVielSepBisRut2.h"

void FehlerWSZuVielSepBisRut2::entry() {
	actions->fehlerHoch();
	cout << "[FEHLER] Auf Foerderbandmodul 2 wurde ein Werkstueck unerwartet aussortiert." << endl;
	cout << "Bitte entfernen Sie das entsprechende Werkstueck aus der Rutsche" << endl;
}

void FehlerWSZuVielSepBisRut2::exit() {
}

void FehlerWSZuVielSepBisRut2::LsRutAn() {
}

void FehlerWSZuVielSepBisRut2::WsAussortieren() {
}

void FehlerWSZuVielSepBisRut2::AuswerferEinfahren() {
}

void FehlerWSZuVielSepBisRut2::quittiert() {
	new (this) QuittiertWSZuVielSepBisRut2;
	entry();
}

void FehlerWSZuVielSepBisRut2::keinFehler() {
}

void FehlerWSZuVielSepBisRut2::Fverschwunden() {
}

void FehlerWSZuVielSepBisRut2::eStop() {
	new (this) WarteSepBisRut2;
}
