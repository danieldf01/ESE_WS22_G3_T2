/*
 * QuittiertWSVerschwundenLSA2.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "QuittiertWSVerschwundenLSA2.h"

void QuittiertWSVerschwundenLSA2::entry() {
	actions->fehlerRunter();
}

void QuittiertWSVerschwundenLSA2::exit() {
}

void QuittiertWSVerschwundenLSA2::lsAnfangAn() {
}

void QuittiertWSVerschwundenLSA2::fbm1WsLosgeschickt() {
}

void QuittiertWSVerschwundenLSA2::fbm1WsUebergeben() {
}

void QuittiertWSVerschwundenLSA2::lsAnfangAus() {
}

void QuittiertWSVerschwundenLSA2::quittiert() {
}

void QuittiertWSVerschwundenLSA2::keinFehler() {
	new (this) WarteAufFBM2;
}

void QuittiertWSVerschwundenLSA2::fehlerVerschwunden(){
}

void QuittiertWSVerschwundenLSA2::eStop() {
	actions->eStop();
	new (this) WarteAufFBM2;
}

void QuittiertWSVerschwundenLSA2::fbm1Bereit() {
}

void QuittiertWSVerschwundenLSA2::fbm2Bereit() {
}
