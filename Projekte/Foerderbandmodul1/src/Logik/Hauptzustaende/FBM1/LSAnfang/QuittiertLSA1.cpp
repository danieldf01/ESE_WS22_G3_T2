/*
 * Quittiert.cpp
 *
 *  Created on: 11.12.2022
 *      Author: Daniel
 */

#include "QuittiertLSA1.h"

using namespace std;

void QuittiertLSA1::entry() {
	actions->fehlerRunter();
}

void QuittiertLSA1::exit() {

}

void QuittiertLSA1::LSan() {

}

void QuittiertLSA1::LSaus() {

}

void QuittiertLSA1::WSstecktFest() {

}

void QuittiertLSA1::quittiert() {

}
void QuittiertLSA1::timerAbstand() {

}

void QuittiertLSA1::keinFehler() {
	exit();
	new (this) WarteAufWsLSA1;
	entry();
}

void QuittiertLSA1::eStop() {
	actions->eStop();
	new (this) WarteAufWsLSA1;
}
