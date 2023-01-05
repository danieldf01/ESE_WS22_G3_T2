/*
 * WarteAbstandWS1.cpp
 *
 *  Created on: 21.12.2022
 *      Author: Marek
 */

#include "WarteAbstandWS1.h"

void WarteAbstandWS1::entry() {
	actions->slq1_aus();
}

void WarteAbstandWS1::exit() {

}

void WarteAbstandWS1::LSan() {
	new (this) FehlerWsAbstand;
	entry();
}

void WarteAbstandWS1::LSaus() {

}

void WarteAbstandWS1::WSstecktFest() {

}

void WarteAbstandWS1::quittiert() {

}
void WarteAbstandWS1::timerAbstand() {
	new (this) WarteAufWsLSA1;
	entry();
}

void WarteAbstandWS1::keinFehler() {

}

void WarteAbstandWS1::eStop() {
	actions->eStop();
	new (this) WarteAufWsLSA1;
}

