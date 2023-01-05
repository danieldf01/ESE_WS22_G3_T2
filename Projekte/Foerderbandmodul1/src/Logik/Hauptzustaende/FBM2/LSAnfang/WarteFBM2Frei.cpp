/*
 * WarteFBM2Frei.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "WarteFBM2Frei.h"

void WarteFBM2Frei::entry() {
}

void WarteFBM2Frei::exit() {
}

void WarteFBM2Frei::lsAnfangAn() {
	new (this) FehlerWSZuVielAufFBM2;
	entry();
}

void WarteFBM2Frei::fbm1WsLosgeschickt() {
}

void WarteFBM2Frei::fbm1WsUebergeben() {
}

void WarteFBM2Frei::lsAnfangAus() {
}

void WarteFBM2Frei::quittiert() {
}

void WarteFBM2Frei::keinFehler() {
}

void WarteFBM2Frei::fbm1Bereit() {
}

void WarteFBM2Frei::fbm2Bereit() {
	new (this) WarteAufFBM2;
}

void WarteFBM2Frei::fehlerVerschwunden(){
}

void WarteFBM2Frei::eStop() {
	actions->eStop();
	new (this) WarteAufFBM2;
}
