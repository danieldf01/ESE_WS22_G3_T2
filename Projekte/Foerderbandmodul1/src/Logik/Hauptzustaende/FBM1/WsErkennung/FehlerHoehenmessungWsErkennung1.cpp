/*
 * FehlerHoehenmessungWsErkennung1.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "FehlerHoehenmessungWsErkennung1.h"

void FehlerHoehenmessungWsErkennung1::entry(){
	actions->fehlerHoch();
	actions->deleteWsHoehensensor();
}

void FehlerHoehenmessungWsErkennung1::exit(){

}

void FehlerHoehenmessungWsErkennung1::WSinHS(){

}

void FehlerHoehenmessungWsErkennung1::WsTyp(){

}

void FehlerHoehenmessungWsErkennung1::quittiert(){
	exit();
	actions->schnellRunter();
	new (this) QuittiertWsErkennung1;
	entry();
}

void FehlerHoehenmessungWsErkennung1::keinFehler(){

}

void FehlerHoehenmessungWsErkennung1::fehlerHoehenmessung(){

}

void FehlerHoehenmessungWsErkennung1::eStop(){
	exit();
	actions->eStop();
	new (this) WartenWsErkennung1;
	entry();
}
