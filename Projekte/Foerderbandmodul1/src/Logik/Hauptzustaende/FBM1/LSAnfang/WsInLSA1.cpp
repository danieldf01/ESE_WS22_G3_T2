/*
 * WSinLSAnfang.cpp
 *
 *  Created on: 11.12.2022
 *      Author: Daniel
 */

#include "WsInLSA1.h"

void WsInLSA1::entry() {

}

void WsInLSA1::exit() {

}

void WsInLSA1::LSan() {

}

void WsInLSA1::LSaus() {
	exit();
	actions->WSinLSAbisHS();
	new (this) WarteAbstandWS1;
	entry();
}

void WsInLSA1::WSstecktFest() {
	exit();
	new (this) FehlerWsStecktFestLSA1;
	entry();
}

void WsInLSA1::quittiert() {

}

void WsInLSA1::keinFehler() {

}

void WsInLSA1::timerAbstand() {

}

void WsInLSA1::eStop() {
	actions->eStop();
	new (this) WarteAufWsLSA1;
}
