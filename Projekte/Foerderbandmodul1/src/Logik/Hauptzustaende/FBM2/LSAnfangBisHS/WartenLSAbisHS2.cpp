/*
 * WartenLSAbisHS.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "WartenLSAbisHS2.h"

void WartenLSAbisHS2::entry(){

}

void WartenLSAbisHS2::exit(){

}

void WartenLSAbisHS2::WSinLSAbisHS(){
	new (this) WsAufWegZumHsLSAbisHS2;
}

void WartenLSAbisHS2::HSaktiv(){
	new (this) FehlerWsZuVielLSAbisHS2;
	entry();
}

void WartenLSAbisHS2::quittiert(){

}

void WartenLSAbisHS2::keinFehler(){

}

void WartenLSAbisHS2::Fverschwunden(){

}

void WartenLSAbisHS2::eStop(){
	actions->eStop();
}
