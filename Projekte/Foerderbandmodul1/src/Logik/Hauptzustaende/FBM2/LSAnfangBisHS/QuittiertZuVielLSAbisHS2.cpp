/*
 * QuittiertZuVielLSAbisHS.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "QuittiertZuVielLSAbisHS2.h"

void QuittiertZuVielLSAbisHS2::entry(){
	actions->fehlerRunter();
	actions->HSleeren();
}

void QuittiertZuVielLSAbisHS2::exit(){

}

void QuittiertZuVielLSAbisHS2::WSinLSAbisHS(){

}

void QuittiertZuVielLSAbisHS2::HSaktiv(){

}

void QuittiertZuVielLSAbisHS2::quittiert(){

}

void QuittiertZuVielLSAbisHS2::keinFehler(){
	exit();
	new (this) WartenLSAbisHS2;
	entry();
}

void QuittiertZuVielLSAbisHS2::Fverschwunden(){

}

void QuittiertZuVielLSAbisHS2::eStop(){
	exit();
	actions->eStop();
	new (this) WartenLSAbisHS2;
	entry();
}
