/*
 * QuittiertWsErkennung2.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "QuittiertWsErkennung2.h"

void QuittiertWsErkennung2::entry(){
	actions->fehlerRunter();
}

void QuittiertWsErkennung2::exit(){

}

void QuittiertWsErkennung2::WSinHS(){

}

void QuittiertWsErkennung2::WsTyp(){

}

void QuittiertWsErkennung2::quittiert(){

}

void QuittiertWsErkennung2::keinFehler(){
	actions->sendFBM2Bereit();
	new (this) WartenWsErkennung2;
}

void QuittiertWsErkennung2::fehlerHoehenmessung(){

}

void QuittiertWsErkennung2::eStop(){
	actions->eStop();
	new (this) WartenWsErkennung2;
}
