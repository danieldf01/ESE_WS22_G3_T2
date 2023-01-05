/*
 * FehlerWsAbstand.cpp
 *
 *  Created on: 21.12.2022
 *      Author: Marek
 */

#include "FehlerWsAbstand.h"

using namespace std;

void FehlerWsAbstand::entry() {
	actions->fehlerHoch();
	cout << "[FEHLER] Auf Foederbandmodul 1 wurde ein Werkstueck mit zu wenig Abstand zum vorherigen eingelegt." << endl;
	cout << "Bitte entfernen Sie das zuletzt am Anfang eingelegte Werkstueck." << endl;
}

void FehlerWsAbstand::exit() {

}

void FehlerWsAbstand::LSan() {

}

void FehlerWsAbstand::LSaus() {

}

void FehlerWsAbstand::WSstecktFest() {

}

void FehlerWsAbstand::quittiert() {
	new (this) QuittiertWsAbstand;
	entry();
}
void FehlerWsAbstand::timerAbstand() {

}

void FehlerWsAbstand::keinFehler() {

}

void FehlerWsAbstand::eStop() {
	actions->eStop();
	new (this) WarteAufWsLSA1;
}

