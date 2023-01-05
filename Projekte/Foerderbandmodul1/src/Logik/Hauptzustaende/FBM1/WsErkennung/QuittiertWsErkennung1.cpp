/*
 * QuittiertWsErkennung1.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "QuittiertWsErkennung1.h"

void QuittiertWsErkennung1::entry(){
	actions->fehlerRunter();
}

void QuittiertWsErkennung1::exit(){

}

void QuittiertWsErkennung1::WSinHS(){

}

void QuittiertWsErkennung1::WsTyp(){

}

void QuittiertWsErkennung1::quittiert(){

}

void QuittiertWsErkennung1::keinFehler(){
	exit();
	new (this) WartenWsErkennung1;
	entry();
}

void QuittiertWsErkennung1::fehlerHoehenmessung(){

}

void QuittiertWsErkennung1::eStop(){
	exit();
	actions->eStop();
	new (this) WartenWsErkennung1;
	entry();
}
