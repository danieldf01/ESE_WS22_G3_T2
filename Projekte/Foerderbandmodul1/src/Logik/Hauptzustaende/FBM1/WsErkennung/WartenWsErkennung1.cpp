/*
 * WartenWsErkennung1.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "WartenWsErkennung1.h"

void WartenWsErkennung1::entry(){

}

void WartenWsErkennung1::exit(){

}

void WartenWsErkennung1::WSinHS(){
	exit();
	new (this) WarteMessungWsErkennung1;
	entry();
}

void WartenWsErkennung1::WsTyp(){

}

void WartenWsErkennung1::quittiert(){

}

void WartenWsErkennung1::keinFehler(){

}

void WartenWsErkennung1::fehlerHoehenmessung(){

}

void WartenWsErkennung1::eStop(){
	actions->eStop();
}
