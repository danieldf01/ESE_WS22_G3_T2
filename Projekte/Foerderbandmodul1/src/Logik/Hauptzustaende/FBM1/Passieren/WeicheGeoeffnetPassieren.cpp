/*
 * WeicheGeoeffnetPassieren.cpp
 *
 *  Created on: 07.01.2023
 *      Author: Daniel Drefs Fernandes
 */

#include "WeicheGeoeffnetPassieren.h"

using namespace std;

void WeicheGeoeffnetPassieren::entry(){

}

void WeicheGeoeffnetPassieren::exit(){

}

void WeicheGeoeffnetPassieren::WsPassieren(){

}

void WeicheGeoeffnetPassieren::WeicheSchliessen(){
	actions->seperatorAus();
	actions->WsAufWegZuLSE();
	new (this) WartenPassieren;
}

void WeicheGeoeffnetPassieren::eStop(){
	actions->eStop();
	new (this) WartenPassieren;
}
