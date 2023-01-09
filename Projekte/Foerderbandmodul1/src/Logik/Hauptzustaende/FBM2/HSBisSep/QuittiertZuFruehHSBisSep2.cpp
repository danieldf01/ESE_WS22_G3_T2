/*
 * QuittiertZuFruehHSBisSep2.cpp
 *
 *  Created on: 19.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "QuittiertZuFruehHSBisSep2.h"

void QuittiertZuFruehHSBisSep2::entry() {
	actions->fehlerRunter();
}

void QuittiertZuFruehHSBisSep2::exit() {
}

void QuittiertZuFruehHSBisSep2::WSinHSbisSep() {
}

void QuittiertZuFruehHSBisSep2::MetSenAn() {
}

void QuittiertZuFruehHSBisSep2::LSSepAn() {
}

void QuittiertZuFruehHSBisSep2::aussortieren1(){

}

void QuittiertZuFruehHSBisSep2::aussortieren2(){

}

void QuittiertZuFruehHSBisSep2::aussortieren3(){

}

void QuittiertZuFruehHSBisSep2::quittiert() {
}

void QuittiertZuFruehHSBisSep2::keinFehler() {
	new (this) WSAufWegZumSep2;
}

void QuittiertZuFruehHSBisSep2::fehlerCntDown(){

}

void QuittiertZuFruehHSBisSep2::fehlerVerschwunden(){

}

void QuittiertZuFruehHSBisSep2::eStop() {
	actions->eStop();
	new (this) WartenHSBisSep2;
}
