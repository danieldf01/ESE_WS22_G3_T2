/*
 * FehlerWSVerschwundenSepBisRut2.cpp
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */
// TODO STILL WORKING
#include "FehlerWSVerschwundenSepBisRut2.h"

void FehlerWSVerschwundenSepBisRut2::entry() {
	actions->fehlerHoch();
	cout << "[FEHLER] Auf Foerderbandmodul 2 ist ein auszusortierendes Werkstueck verschwunden, bevor es die Rutsche erreicht hat." << endl;
	cout << "Eventuell ist es vom Foerderband gefallen. Bitte entfernen Sie das entsprechende Werkstueck, falls es sich noch auf dem Modul befindet." << endl;
}

void FehlerWSVerschwundenSepBisRut2::exit() {
}

void FehlerWSVerschwundenSepBisRut2::LsRutAn() {
}

void FehlerWSVerschwundenSepBisRut2::WsAussortieren() {
}

void FehlerWSVerschwundenSepBisRut2::AuswerferEinfahren() {
}

void FehlerWSVerschwundenSepBisRut2::quittiert() {
	new (this) QuittiertWSVerschwundenSepBisRut2;
	entry();
}

void FehlerWSVerschwundenSepBisRut2::keinFehler() {
}

void FehlerWSVerschwundenSepBisRut2::Fverschwunden() {
}

void FehlerWSVerschwundenSepBisRut2::eStop() {
}
