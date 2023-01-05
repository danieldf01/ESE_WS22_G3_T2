/*
 * FehlerWSZuVielLSA2.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "FehlerWSZuVielLSA2.h"

void FehlerWSZuVielLSA2::entry() {
	actions->fehlerHoch();
	cout << "[FEHLER] Auf Foerderbandmodul 2 wurde ein unerwarteter Stoerfaktor (evtl. ein Werkstueck) erkannt." << endl;
	cout << "Bitte entfernen Sie den Stoerfaktor und/oder alle Werkstuecke an der Lichtschranke am Anfang." << endl;
}

void FehlerWSZuVielLSA2::exit() {
}

void FehlerWSZuVielLSA2::lsAnfangAn() {
}

void FehlerWSZuVielLSA2::fbm1WsLosgeschickt() {
}

void FehlerWSZuVielLSA2::fbm1WsUebergeben() {
}

void FehlerWSZuVielLSA2::lsAnfangAus() {
}

void FehlerWSZuVielLSA2::quittiert() {
	new (this) QuittiertWSZuVielLSA2;
	entry();
}

void FehlerWSZuVielLSA2::keinFehler() {
}

void FehlerWSZuVielLSA2::fbm1Bereit() {
}

void FehlerWSZuVielLSA2::fbm2Bereit() {
}

void FehlerWSZuVielLSA2::fehlerVerschwunden(){
}

void FehlerWSZuVielLSA2::eStop() {
	actions->eStop();
	new (this) WarteAufFBM2;
}
