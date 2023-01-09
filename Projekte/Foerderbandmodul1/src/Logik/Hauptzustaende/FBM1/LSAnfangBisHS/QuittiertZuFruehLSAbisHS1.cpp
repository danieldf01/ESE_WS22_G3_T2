/*
 * QuittiertZuFruehLSAbisHS.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "QuittiertZuFruehLSAbisHS1.h"

void QuittiertZuFruehLSAbisHS1::entry(){
	actions->fehlerRunter();
}

void QuittiertZuFruehLSAbisHS1::exit(){

}

void QuittiertZuFruehLSAbisHS1::WSinLSAbisHS(){

}

void QuittiertZuFruehLSAbisHS1::HSaktiv(){

}

void QuittiertZuFruehLSAbisHS1::quittiert(){

}

void QuittiertZuFruehLSAbisHS1::keinFehler(){
	exit();
	new (this) WsAufWegZumHsLSAbisHS1;
	entry();
}

void QuittiertZuFruehLSAbisHS1::Fverschwunden(){

}

void QuittiertZuFruehLSAbisHS1::eStop(){
	exit();
	actions->eStop();
	new (this) WartenLSAbisHS1;
	entry();
}
