/*
 * WSInLSA2.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "WSInLSA2.h"

void WSInLSA2::entry() {
}

void WSInLSA2::exit() {
}

void WSInLSA2::lsAnfangAn() {
}

void WSInLSA2::fbm1WsLosgeschickt() {
}

void WSInLSA2::fbm1WsUebergeben() {
}

void WSInLSA2::lsAnfangAus() {
	cout << "[FBM2] WSInLSA2 recv: lsAnfangAus" << endl;
	actions->WSinLSAbisHS();
	new (this) WarteFBM2Frei;
}

void WSInLSA2::quittiert() {
}

void WSInLSA2::keinFehler() {
}

void WSInLSA2::fehlerVerschwunden(){
}

void WSInLSA2::eStop() {
	actions->eStop();
}

void WSInLSA2::fbm1Bereit() {
}

void WSInLSA2::fbm2Bereit() {
}
