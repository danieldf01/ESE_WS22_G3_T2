/*
 * QuittiertWSZuVielSepBisRut2.cpp
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */

#include "QuittiertWSZuVielSepBisRut2.h"

void QuittiertWSZuVielSepBisRut2::entry() {
	actions->fehlerRunter();
}

void QuittiertWSZuVielSepBisRut2::exit() {
}

void QuittiertWSZuVielSepBisRut2::LsRutAn() {
}

void QuittiertWSZuVielSepBisRut2::WsAussortieren() {
}

void QuittiertWSZuVielSepBisRut2::AuswerferEinfahren() {
}

void QuittiertWSZuVielSepBisRut2::quittiert() {
}

void QuittiertWSZuVielSepBisRut2::keinFehler() {
	new (this) WarteSepBisRut2;
}

void QuittiertWSZuVielSepBisRut2::Fverschwunden() {
}

void QuittiertWSZuVielSepBisRut2::eStop() {
	new (this) WarteSepBisRut2;
}
