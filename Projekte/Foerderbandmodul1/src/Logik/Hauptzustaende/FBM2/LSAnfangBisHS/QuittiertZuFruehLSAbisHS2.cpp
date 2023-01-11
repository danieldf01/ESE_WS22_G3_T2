/*
 * QuittiertZuFruehLSAbisHS.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "QuittiertZuFruehLSAbisHS2.h"

void QuittiertZuFruehLSAbisHS2::entry(){
	actions->fehlerRunter();
}

void QuittiertZuFruehLSAbisHS2::exit(){

}

void QuittiertZuFruehLSAbisHS2::WSinLSAbisHS(){

}

void QuittiertZuFruehLSAbisHS2::HSaktiv(){

}

void QuittiertZuFruehLSAbisHS2::quittiert(){

}

void QuittiertZuFruehLSAbisHS2::keinFehler(){
	new (this) WsAufWegZumHsLSAbisHS2;
}

void QuittiertZuFruehLSAbisHS2::Fverschwunden(){

}

void QuittiertZuFruehLSAbisHS2::eStop(){
	actions->eStop();
	new (this) WartenLSAbisHS2;
}
