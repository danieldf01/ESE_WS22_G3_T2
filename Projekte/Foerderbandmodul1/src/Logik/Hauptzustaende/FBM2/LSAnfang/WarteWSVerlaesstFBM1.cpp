/*
 * WarteWSVerlaestFBM1.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "WarteWSVerlaesstFBM1.h"

void WarteWSVerlaesstFBM1::entry() {
}

void WarteWSVerlaesstFBM1::exit() {
}

void WarteWSVerlaesstFBM1::lsAnfangAn() {
	new (this)FehlerWSZuFruehLSA2;
	entry();
}

void WarteWSVerlaesstFBM1::fbm1WsLosgeschickt() {
}

void WarteWSVerlaesstFBM1::fbm1WsUebergeben() {
	new (this) WSZwischenFBM1FBM2;
}

void WarteWSVerlaesstFBM1::lsAnfangAus() {
}

void WarteWSVerlaesstFBM1::quittiert() {
}

void WarteWSVerlaesstFBM1::keinFehler() {
}

void WarteWSVerlaesstFBM1::fehlerVerschwunden(){
}

void WarteWSVerlaesstFBM1::eStop() {
	actions->eStop();
	new (this) WarteAufFBM2;
}

void WarteWSVerlaesstFBM1::fbm1Bereit() {
}

void WarteWSVerlaesstFBM1::fbm2Bereit() {
}
