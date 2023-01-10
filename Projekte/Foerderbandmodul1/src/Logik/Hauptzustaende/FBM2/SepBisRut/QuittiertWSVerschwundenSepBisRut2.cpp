/*
 * QuittiertWSVerschwundenSepBisRut2.cpp
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */

#include "QuittiertWSVerschwundenSepBisRut2.h"

void QuittiertWSVerschwundenSepBisRut2::entry() {
	actions->fehlerRunter();
}

void QuittiertWSVerschwundenSepBisRut2::exit() {
}

void QuittiertWSVerschwundenSepBisRut2::LsRutAn() {
}

void QuittiertWSVerschwundenSepBisRut2::WsAussortieren() {
}

void QuittiertWSVerschwundenSepBisRut2::AuswerferEinfahren() {
}

void QuittiertWSVerschwundenSepBisRut2::quittiert() {
}

void QuittiertWSVerschwundenSepBisRut2::keinFehler() {
	actions->deleteTimerVerschwunden(); // TODO Hier timer delete?
	actions->schnellRunter();
	actions->zerstoereWsAussortieren();
	actions->sendFBM2Bereit();
	new (this) WarteSepBisRut2;
}

void QuittiertWSVerschwundenSepBisRut2::Fverschwunden() {
}

void QuittiertWSVerschwundenSepBisRut2::eStop() {
	new (this) WarteSepBisRut2;
}
