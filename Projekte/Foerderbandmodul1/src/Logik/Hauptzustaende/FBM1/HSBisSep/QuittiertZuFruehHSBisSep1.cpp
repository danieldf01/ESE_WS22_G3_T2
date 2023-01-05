/*
 * QuittiertZuFruehHSBisSep1.cpp
 *
 *  Created on: 19.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "QuittiertZuFruehHSBisSep1.h"

void QuittiertZuFruehHSBisSep1::entry() {
	actions->fehlerRunter();
}

void QuittiertZuFruehHSBisSep1::exit() {
}

void QuittiertZuFruehHSBisSep1::WSinHSbisSep() {
}

void QuittiertZuFruehHSBisSep1::MetSenAn() {
}

void QuittiertZuFruehHSBisSep1::LSSepAn() {
}

void QuittiertZuFruehHSBisSep1::aussortieren1(){

}

void QuittiertZuFruehHSBisSep1::aussortieren2(){

}

void QuittiertZuFruehHSBisSep1::aussortieren3(){

}

void QuittiertZuFruehHSBisSep1::aussortieren4(){

}

void QuittiertZuFruehHSBisSep1::quittiert() {
}

void QuittiertZuFruehHSBisSep1::keinFehler() {
	exit();
	new (this) WSAufWegZumSep1;
}

void QuittiertZuFruehHSBisSep1::fehlerCntDown(){

}

void QuittiertZuFruehHSBisSep1::fehlerVerschwunden(){

}

void QuittiertZuFruehHSBisSep1::eStop() {
	exit();
	actions->eStop();
	new (this) WartenHSBisSep1;
	entry();
}
