/*
 * FehlerRutsche1Und2Voll.cpp
 *
 *  Created on: 21.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "FehlerRutsche1Und2Voll.h"

void FehlerRutsche1Und2Voll::entry(){
	actions->fehlerHoch();
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
