/*
 * FehlerHoehenmessungWsErkennung2.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "FehlerHoehenmessungWsErkennung2.h"

void FehlerHoehenmessungWsErkennung2::entry(){
	actions->fehlerHoch();
	actions->deleteWsHoehensensor();
}

void FehlerHoehenmessungWsErkennung2::exit(){

}

void FehlerHoehenmessungWsErkennung2::WSinHS(){

}

void FehlerHoehenmessungWsErkennung2::WsTyp(){

}

void FehlerHoehenmessungWsErkennung2::quittiert(){
	exit();
	actions->schnellRunter();
	new (this) QuittiertWsErkennung2;
	entry();
}

void FehlerHoehenmessungWsErkennung2::keinFehler(){

}

void FehlerHoehenmessungWsErkennung2::fehlerHoehenmessung(){

}

void FehlerHoehenmessungWsErkennung2::eStop(){
	exit();
	actions->eStop();
	new (this) WartenWsErkennung2;
	entry();
}
