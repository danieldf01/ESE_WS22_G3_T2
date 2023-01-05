/*
 * FehlerWSVerschwundenLSA2.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "FehlerWSVerschwundenLSA2.h"

void FehlerWSVerschwundenLSA2::entry() {
	actions->fehlerHoch();
	actions->entferneWsLSA2();
	cout << "[FEHLER] Es ist ein Werkstueck beim Uebergang von Foerderbandmodul 1 auf Foerderbandmodul 2 verschwunden." << endl;
	cout << "Bitte entfernen Sie alle Werkstuecke, die sich moeglicherweise noch zwischen den Modulen oder auf Foerderbandmodul 2 befinden." << endl;
}

void FehlerWSVerschwundenLSA2::exit() {
}

void FehlerWSVerschwundenLSA2::lsAnfangAn() {
}

void FehlerWSVerschwundenLSA2::fbm1WsLosgeschickt() {
}

void FehlerWSVerschwundenLSA2::fbm1WsUebergeben() {
}

void FehlerWSVerschwundenLSA2::lsAnfangAus() {
}

void FehlerWSVerschwundenLSA2::quittiert() {
	actions->schnellRunter();
	actions->schnellRunter1();
	new (this) QuittiertWSVerschwundenLSA2;
	entry();
}

void FehlerWSVerschwundenLSA2::keinFehler() {
}

void FehlerWSVerschwundenLSA2::fbm1Bereit() {
}

void FehlerWSVerschwundenLSA2::fbm2Bereit() {
}

void FehlerWSVerschwundenLSA2::fehlerVerschwunden(){
}

void FehlerWSVerschwundenLSA2::eStop() {
	actions->eStop();
	new (this) WarteAufFBM2;
}
