/*
 * ImMetallsensorHSBisSep2.cpp
 *
 *  Created on: 17.12.2022
 *      Author: tobias
 */

#include "ImMetallsensorHSBisSep2.h"

void ImMetallsensorHSBisSep2::entry() {
}

void ImMetallsensorHSBisSep2::exit() {
}

void ImMetallsensorHSBisSep2::WSinHSbisSep() {
}

void ImMetallsensorHSBisSep2::MetSenAn() {
}

void ImMetallsensorHSBisSep2::LSSepAn() {
	exit();
	actions->deleteTimerVerschwunden();
	// TODO Zeit anpassen
	aussortieren1();
	entry();
}

void ImMetallsensorHSBisSep2::quittiert() {
}

void ImMetallsensorHSBisSep2::keinFehler() {
}

void ImMetallsensorHSBisSep2::fehlerCntDown() {

}

void ImMetallsensorHSBisSep2::fehlerVerschwunden() {
	exit();
	new (this) FehlerWsVerschwundenHSBisSep2;
	entry();
}

void ImMetallsensorHSBisSep2::eStop() {
	exit();
	actions->eStop();
	new (this) WartenHSBisSep2;
	entry();
}

void ImMetallsensorHSBisSep2::aussortieren1() {
	//Fehler zu frueh?
//	if (zeitmanager->getTime()< (500 + wsListen->ws_list_HS_bis_Seperator_2.front().getTimestamp())) {
//		new (this) FehlerWsZuFruehHSBisSep2;
//	} else {
//		aussortieren2();
//	}
}

void ImMetallsensorHSBisSep2::aussortieren2() {
	//ist das aktuelle Werkstueck vom geforderten Typ?
//	if (wsListen->ws_list_HS_bis_Seperator_2.front().getWsTyp() == wsListen->sortierReihenfolge.front()) {
//		cout << "Werkstueck entspricht der Reihung" << endl;
//		actions->WsPassierenGefordert();
//		if (wsListen->ws_list_HS_bis_Seperator_2.size() <= 0) {
//			new (this) WartenHSBisSep2;
//		}
//		//nicht geforderter Typ
//	} else {
//		cout << "Werkstueck entspricht nicht der Reihung" << endl;
//		aussortieren3();
//	}
}
// TODO Folgende Methode muss unebedingt angepasst werden!
void ImMetallsensorHSBisSep2::aussortieren3() {
	// Ist Rutsche2 voll?
//	if (rutsche->rutsche2->rutscheVoll) {
//		// TODO Action WS_NICHT_AUSSORTIERBAR
//	}else{
//		// TODO Uebergang in die Rutsche
//	}
}
