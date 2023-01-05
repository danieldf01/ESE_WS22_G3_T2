/*
 * FehlerWSZuVielSepBisRut1.cpp
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */
 // TODO DONE
#include "FehlerWSZuVielSepBisRut1.h"

void FehlerWSZuVielSepBisRut1::entry() {
	actions->fehlerHoch();
	cout << "[FEHLER] Auf Foerderbandmodul 1 wurde ein Werkstueck unerwartet aussortiert." << endl;
	cout << "Bitte entfernen Sie das entsprechende Werkstueck aus der Rutsche" << endl;
}

void FehlerWSZuVielSepBisRut1::exit() {
}

void FehlerWSZuVielSepBisRut1::LsRutAn() {
}

void FehlerWSZuVielSepBisRut1::WsAussortieren() {
}

void FehlerWSZuVielSepBisRut1::AuswerferEinfahren() {
}

void FehlerWSZuVielSepBisRut1::quittiert() {
	exit();
	new (this) QuittiertWSZuVielSepBisRut1;
	entry();
}

void FehlerWSZuVielSepBisRut1::keinFehler() {
}

void FehlerWSZuVielSepBisRut1::Fverschwunden() {
}

void FehlerWSZuVielSepBisRut1::eStop() {
}
