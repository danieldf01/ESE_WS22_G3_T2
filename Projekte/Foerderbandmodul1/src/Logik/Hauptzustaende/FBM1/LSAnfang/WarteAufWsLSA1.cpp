/*
 * WarteAufWS.cpp
 *
 *  Created on: 11.12.2022
 *      Author: Daniel
 */

#include "WarteAufWsLSA1.h"

using namespace std;

void WarteAufWsLSA1::entry() {
	actions->slq1_an();
}

void WarteAufWsLSA1::exit() {

}

void WarteAufWsLSA1::LSan() {
	exit();
	actions->schnellHoch();
	actions->erstelleWS();
	new (this) WsInLSA1;
	entry();
}

void WarteAufWsLSA1::LSaus() {

}
void WarteAufWsLSA1::timerAbstand() {

}

void WarteAufWsLSA1::WSstecktFest() {

}

void WarteAufWsLSA1::quittiert() {

}

void WarteAufWsLSA1::keinFehler() {

}

void WarteAufWsLSA1::eStop() {
	actions->eStop();
	new (this) WarteAufWsLSA1;
}
