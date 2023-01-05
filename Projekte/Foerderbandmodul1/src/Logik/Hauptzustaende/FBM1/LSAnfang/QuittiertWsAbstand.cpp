/*
 * QuittiertWsAbstand.cpp
 *
 *  Created on: 21.12.2022
 *      Author: Marek
 */

#include "QuittiertWsAbstand.h"

void QuittiertWsAbstand::entry() {
	actions->fehlerRunter();
}

void QuittiertWsAbstand::exit() {

}

void QuittiertWsAbstand::LSan() {

}

void QuittiertWsAbstand::LSaus() {

}

void QuittiertWsAbstand::WSstecktFest() {

}

void QuittiertWsAbstand::quittiert() {

}
void QuittiertWsAbstand::timerAbstand() {

}

void QuittiertWsAbstand::keinFehler() {
	new (this) WarteAbstandWS1;
	entry();
}

void QuittiertWsAbstand::eStop() {
	actions->eStop();
	new (this) WarteAufWsLSA1;
}

