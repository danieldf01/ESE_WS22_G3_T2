/*
 * QuittiertWSZuFruehLSA2.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "QuittiertWSZuFruehLSA2.h"

void QuittiertWSZuFruehLSA2::entry() {
	actions->fehlerRunter();
}

void QuittiertWSZuFruehLSA2::exit() {
}

void QuittiertWSZuFruehLSA2::lsAnfangAn() {
}

void QuittiertWSZuFruehLSA2::fbm1WsLosgeschickt() {
}

void QuittiertWSZuFruehLSA2::fbm1WsUebergeben() {
}

void QuittiertWSZuFruehLSA2::lsAnfangAus() {
}

void QuittiertWSZuFruehLSA2::quittiert() {
}

void QuittiertWSZuFruehLSA2::keinFehler() {
	new (this) WarteWSVerlaesstFBM1;
}

void QuittiertWSZuFruehLSA2::fehlerVerschwunden(){
}

void QuittiertWSZuFruehLSA2::eStop() {
	actions->eStop();
	new (this) WarteAufFBM2;
}

void QuittiertWSZuFruehLSA2::fbm1Bereit() {
}

void QuittiertWSZuFruehLSA2::fbm2Bereit() {
}
