/*
 * QuittiertVerschwundenLSAbisHS.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "QuittiertVerschwundenLSAbisHS2.h"

void QuittiertVerschwundenLSAbisHS2::entry(){
	actions->fehlerRunter();
}

void QuittiertVerschwundenLSAbisHS2::exit(){

}

void QuittiertVerschwundenLSAbisHS2::WSinLSAbisHS(){

}

void QuittiertVerschwundenLSAbisHS2::HSaktiv(){

}

void QuittiertVerschwundenLSAbisHS2::quittiert(){

}

void QuittiertVerschwundenLSAbisHS2::keinFehler(){
	actions->sendFBM2Bereit();
	new (this) WartenLSAbisHS2;
}

void QuittiertVerschwundenLSAbisHS2::Fverschwunden(){

}

void QuittiertVerschwundenLSAbisHS2::eStop(){
	actions->eStop();
	new (this) WartenLSAbisHS2;
}
