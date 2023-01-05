/*
 * FehlerRutsche2Voll.cpp
 *
 *  Created on: 21.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "FehlerRutsche2Voll.h"

void FehlerRutsche2Voll::entry(){
	actions->fehlerHoch();
}

void FehlerRutsche2Voll::exit(){
	actions->fehlerRunter();
}

void FehlerRutsche2Voll::WsNichtAussortierbar(){

}

void FehlerRutsche2Voll::LsRutscheAus1(){

}

void FehlerRutsche2Voll::LsRutscheAus2(){
	exit();
	new (this) WartenWsNichtAussortierbar;
	entry();
}

void FehlerRutsche2Voll::eStop(){
	new (this) WartenWsNichtAussortierbar;
}
