/*
 * FehlerRutsche1Und2Voll.cpp
 *
 *  Created on: 21.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "FehlerRutsche1Und2Voll.h"
using namespace std;
void FehlerRutsche1Und2Voll::entry(){
	actions->fehlerHoch();
	cout << "[FEHLER] Die Rutschen auf beiden Foerderbandmodulen sind voll, es kann kein Werkstueck aussortiert werden!" << endl;
	cout << "Bitte entfernen Sie alle Werkstuecke aus den Rutschen" << endl;
}

void FehlerRutsche1Und2Voll::exit(){
	actions->fehlerRunter();
}

void FehlerRutsche1Und2Voll::WsNichtAussortierbar(){

}

void FehlerRutsche1Und2Voll::LsRutscheAus1(){
	exit();
	new (this) WartenWsNichtAussortierbar;
	entry();
}

void FehlerRutsche1Und2Voll::LsRutscheAus2(){
	exit();
	new (this) WartenWsNichtAussortierbar;
	entry();
}

void FehlerRutsche1Und2Voll::eStop(){
	new (this) WartenWsNichtAussortierbar;
}
