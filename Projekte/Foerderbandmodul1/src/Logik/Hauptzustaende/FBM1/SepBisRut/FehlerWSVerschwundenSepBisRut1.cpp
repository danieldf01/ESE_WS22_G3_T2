/*
 * FehlerWSVerschwundenSepBisRut1.cpp
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */
// TODO STILL WORKING
#include "FehlerWSVerschwundenSepBisRut1.h"

void FehlerWSVerschwundenSepBisRut1::entry() {
	actions->fehlerHoch();
	cout << "[FEHLER] Auf Foerderbandmodul 1 ist ein auszusortierendes Werkstueck verschwunden, bevor es die Rutsche erreicht hat." << endl;
	cout << "Eventuell ist es vom Foerderband gefallen. Bitte entfernen Sie das entsprechende Werkstueck, falls es sich noch auf dem Modul befindet." << endl;
}

void FehlerWSVerschwundenSepBisRut1::exit() {
}

void FehlerWSVerschwundenSepBisRut1::LsRutAn() {
}

void FehlerWSVerschwundenSepBisRut1::WsAussortieren() {
}

void FehlerWSVerschwundenSepBisRut1::AuswerferEinfahren() {
}

void FehlerWSVerschwundenSepBisRut1::quittiert() {
	new (this) QuittiertWSVerschwundenSepBisRut1;
	entry();
}

void FehlerWSVerschwundenSepBisRut1::keinFehler() {
}

void FehlerWSVerschwundenSepBisRut1::Fverschwunden() {
}

void FehlerWSVerschwundenSepBisRut1::eStop() {
}
