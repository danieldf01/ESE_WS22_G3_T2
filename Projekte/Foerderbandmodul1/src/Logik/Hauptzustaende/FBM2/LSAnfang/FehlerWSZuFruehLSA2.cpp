/*
 * FehlerWSZuFruehLSA2.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "FehlerWSZuFruehLSA2.h"

void FehlerWSZuFruehLSA2::entry() {
	actions->fehlerHoch();
	cout << "[FEHLER] Auf Foerderbandmodul 2 wurde in der Lichtschranke ein Stoerfaktor erkannt (oder ein Werkstueck beim Uebergang nach vorne geschoben)." << endl;
	cout << "Bitte entfernen Sie den Stoerfaktor oder (falls sich 2 Werkstuecke auf FBM2 befinden)" << endl;
	cout <<	"das Werkstueck, das sich am naechsten an der Lichtschranke am Anfang (wahrscheinlich sogar dazwischen) befindet." << endl;
}

void FehlerWSZuFruehLSA2::exit() {
}

void FehlerWSZuFruehLSA2::lsAnfangAn() {
}

void FehlerWSZuFruehLSA2::fbm1WsLosgeschickt() {
}

void FehlerWSZuFruehLSA2::fbm1WsUebergeben() {
}

void FehlerWSZuFruehLSA2::lsAnfangAus() {
}

void FehlerWSZuFruehLSA2::quittiert() {
	new (this) QuittiertWSZuFruehLSA2;
	entry();
}

void FehlerWSZuFruehLSA2::keinFehler() {
}

void FehlerWSZuFruehLSA2::fbm1Bereit() {
}

void FehlerWSZuFruehLSA2::fbm2Bereit() {
}

void FehlerWSZuFruehLSA2::fehlerVerschwunden(){
}

void FehlerWSZuFruehLSA2::eStop() {
	actions->eStop();
	new (this) WarteAufFBM2;
}
