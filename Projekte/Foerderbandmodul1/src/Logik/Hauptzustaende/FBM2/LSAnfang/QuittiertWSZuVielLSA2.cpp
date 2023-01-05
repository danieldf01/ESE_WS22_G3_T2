/*
 * QuittiertWSZuVielLSA2.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "QuittiertWSZuVielLSA2.h"

void QuittiertWSZuVielLSA2::entry() {
	actions->fehlerRunter();
}

void QuittiertWSZuVielLSA2::exit() {
}

void QuittiertWSZuVielLSA2::lsAnfangAn() {
}

void QuittiertWSZuVielLSA2::fbm1WsLosgeschickt() {
}

void QuittiertWSZuVielLSA2::fbm1WsUebergeben() {
}

void QuittiertWSZuVielLSA2::lsAnfangAus() {
}

void QuittiertWSZuVielLSA2::quittiert() {
}

void QuittiertWSZuVielLSA2::keinFehler() {
	new (this) WarteAufFBM2;
}

void QuittiertWSZuVielLSA2::fehlerVerschwunden(){
}

void QuittiertWSZuVielLSA2::eStop() {
	actions->eStop();
	new (this) WarteAufFBM2;
}

void QuittiertWSZuVielLSA2::fbm1Bereit() {
}

void QuittiertWSZuVielLSA2::fbm2Bereit() {
}
