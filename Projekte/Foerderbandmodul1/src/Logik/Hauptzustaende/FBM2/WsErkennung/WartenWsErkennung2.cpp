/*
 * WartenWsErkennung2.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "WartenWsErkennung2.h"

void WartenWsErkennung2::entry(){

}

void WartenWsErkennung2::exit(){

}

void WartenWsErkennung2::WSinHS(){
	actions->speicherWSTyp();
	new (this) WarteMessungWsErkennung2;
}

void WartenWsErkennung2::WsTyp(){

}

void WartenWsErkennung2::quittiert(){

}

void WartenWsErkennung2::keinFehler(){

}

void WartenWsErkennung2::fehlerHoehenmessung(){

}

void WartenWsErkennung2::eStop(){
	actions->eStop();
}
