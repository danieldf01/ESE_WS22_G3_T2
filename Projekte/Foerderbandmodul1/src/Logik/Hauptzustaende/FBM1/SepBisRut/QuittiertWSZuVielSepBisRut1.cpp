/*
 * QuittiertWSZuVielSepBisRut1.cpp
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */

#include "QuittiertWSZuVielSepBisRut1.h"

void QuittiertWSZuVielSepBisRut1::entry() {
	actions->fehlerRunter();
}

void QuittiertWSZuVielSepBisRut1::exit() {
}

void QuittiertWSZuVielSepBisRut1::LsRutAn() {
}

void QuittiertWSZuVielSepBisRut1::WsAussortieren() {
}

void QuittiertWSZuVielSepBisRut1::AuswerferEinfahren() {
}

void QuittiertWSZuVielSepBisRut1::quittiert() {
}

void QuittiertWSZuVielSepBisRut1::keinFehler() {
	exit();
	new (this) WarteSepBisRut1;
	entry();
}

void QuittiertWSZuVielSepBisRut1::Fverschwunden() {
}

void QuittiertWSZuVielSepBisRut1::eStop() {
}
