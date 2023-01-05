/*
 * QuittiertWSZuVielAufFBM2.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "QuittiertWSZuVielAufFBM2.h"

void QuittiertWSZuVielAufFBM2::entry() {
	actions->fehlerRunter();
}

void QuittiertWSZuVielAufFBM2::exit() {
}

void QuittiertWSZuVielAufFBM2::lsAnfangAn() {
}

void QuittiertWSZuVielAufFBM2::fbm1WsLosgeschickt() {
}

void QuittiertWSZuVielAufFBM2::fbm1WsUebergeben() {
}

void QuittiertWSZuVielAufFBM2::lsAnfangAus() {
}

void QuittiertWSZuVielAufFBM2::quittiert() {
}

void QuittiertWSZuVielAufFBM2::keinFehler() {
	new (this) WarteFBM2Frei;
}

void QuittiertWSZuVielAufFBM2::fehlerVerschwunden(){
}

void QuittiertWSZuVielAufFBM2::eStop() {
	actions->eStop();
	new (this) WarteAufFBM2;
}

void QuittiertWSZuVielAufFBM2::fbm1Bereit() {
}

void QuittiertWSZuVielAufFBM2::fbm2Bereit() {
}
