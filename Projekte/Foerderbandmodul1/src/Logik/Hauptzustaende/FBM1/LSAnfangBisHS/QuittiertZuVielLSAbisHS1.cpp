/*
 * QuittiertZuVielLSAbisHS.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "QuittiertZuVielLSAbisHS1.h"

void QuittiertZuVielLSAbisHS1::entry(){
	actions->fehlerRunter();
	actions->HSleeren();
}

void QuittiertZuVielLSAbisHS1::exit(){

}

void QuittiertZuVielLSAbisHS1::WSinLSAbisHS(){

}

void QuittiertZuVielLSAbisHS1::HSaktiv(){

}

void QuittiertZuVielLSAbisHS1::quittiert(){

}

void QuittiertZuVielLSAbisHS1::keinFehler(){
	exit();
	new (this) WartenLSAbisHS1;
	entry();
}

void QuittiertZuVielLSAbisHS1::Fverschwunden(){

}

void QuittiertZuVielLSAbisHS1::eStop(){
	exit();
	actions->eStop();
	new (this) WartenLSAbisHS1;
	entry();
}
