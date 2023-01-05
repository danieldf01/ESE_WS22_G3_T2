/*
 * FehlerWSZuVielAufFBM2.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "FehlerWSZuVielAufFBM2.h"

void FehlerWSZuVielAufFBM2::entry() {
	actions->fehlerHoch();
	cout << "[FEHLER] Auf Foerderbandmodul 2 wurde ein unerwarteter Stoerfaktor (evtl. ein Werkstueck) erkannt." << endl;
	cout << "Bitte entfernen Sie den Stoerfaktor und/oder alle Werkstuecke an der Lichtschranke am Anfang." << endl;
}

void FehlerWSZuVielAufFBM2::exit() {
}

void FehlerWSZuVielAufFBM2::lsAnfangAn() {
}

void FehlerWSZuVielAufFBM2::fbm1WsLosgeschickt() {
}

void FehlerWSZuVielAufFBM2::fbm1WsUebergeben() {
}

void FehlerWSZuVielAufFBM2::lsAnfangAus() {
}

void FehlerWSZuVielAufFBM2::quittiert() {
	new (this) QuittiertWSZuVielAufFBM2;
	entry();
}

void FehlerWSZuVielAufFBM2::keinFehler() {
}

void FehlerWSZuVielAufFBM2::fbm1Bereit() {
}

void FehlerWSZuVielAufFBM2::fbm2Bereit() {
}

void FehlerWSZuVielAufFBM2::fehlerVerschwunden(){
}

void FehlerWSZuVielAufFBM2::eStop() {
	actions->eStop();
	new (this) WarteAufFBM2;
}
