/*
 * WSZwischenFBM1FBM2.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "WSZwischenFBM1FBM2.h"

void WSZwischenFBM1FBM2::entry() {
}

void WSZwischenFBM1FBM2::exit() {
}

void WSZwischenFBM1FBM2::lsAnfangAn() {
	actions->schnellRunter1();
	new (this) WSInLSA2;
}

void WSZwischenFBM1FBM2::fbm1WsLosgeschickt() {
}

void WSZwischenFBM1FBM2::fbm1WsUebergeben() {
}

void WSZwischenFBM1FBM2::lsAnfangAus() {
}

void WSZwischenFBM1FBM2::quittiert() {
}

void WSZwischenFBM1FBM2::keinFehler() {
}

void WSZwischenFBM1FBM2::fehlerVerschwunden(){
	new (this) FehlerWSVerschwundenLSA2;
	entry();
}

void WSZwischenFBM1FBM2::eStop() {
	actions->eStop();
	new (this) WarteAufFBM2;
}

void WSZwischenFBM1FBM2::fbm1Bereit() {
}

void WSZwischenFBM1FBM2::fbm2Bereit() {
}
