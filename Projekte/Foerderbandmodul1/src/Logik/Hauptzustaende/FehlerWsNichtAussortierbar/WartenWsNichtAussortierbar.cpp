/*
 * WartenWsNichtAussortierbar.cpp
 *
 *  Created on: 21.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "WartenWsNichtAussortierbar.h"

using namespace std;
void WartenWsNichtAussortierbar::entry(){

}

void WartenWsNichtAussortierbar::exit(){

}

void WartenWsNichtAussortierbar::WsNichtAussortierbar(){
	exit();
//	cout << "WsNichtAussortierbar erhalten" << endl;
	if(rutsche->rutsche1->rutscheVoll1 && rutsche->rutsche2->rutscheVoll2){
		new (this) FehlerRutsche1Und2Voll;
//		cout << "FehlerRutsche1und2Voll" << endl;
	} else if(!rutsche->rutsche1->rutscheVoll1 && rutsche->rutsche2->rutscheVoll2){
//		cout << "FehlerRutsche2Voll" << endl;
		new (this) FehlerRutsche2Voll;
	}
	entry();
}

void WartenWsNichtAussortierbar::LsRutscheAus1(){

}

void WartenWsNichtAussortierbar::LsRutscheAus2(){

}

void WartenWsNichtAussortierbar::eStop(){

}
