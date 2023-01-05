/*
 * WarteAufFBM2.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "WarteAufFBM2.h"

void WarteAufFBM2::entry() {
}

void WarteAufFBM2::exit() {
}

void WarteAufFBM2::lsAnfangAn() {
	new (this)FehlerWSZuVielLSA2;
	entry();
}

void WarteAufFBM2::fbm1WsLosgeschickt() {
	cout << "[FBM2] WarteAufFBM2 recv: fbm1WsLosgeschickt" << endl;
	actions->schnellHoch();
	new (this)WarteWSVerlaesstFBM1;
}

void WarteAufFBM2::fbm1WsUebergeben() {
}

void WarteAufFBM2::lsAnfangAus() {
}

void WarteAufFBM2::quittiert() {
}

void WarteAufFBM2::keinFehler() {
}

void WarteAufFBM2::fehlerVerschwunden(){
}

void WarteAufFBM2::eStop() {
	actions->eStop();
}

void WarteAufFBM2::fbm1Bereit() {
	actions->sendFBM2Bereit();
}

void WarteAufFBM2::fbm2Bereit() {
}
