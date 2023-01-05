/*
 * QuittiertHSBisSep1.cpp
 *
 *  Created on: 17.12.2022
 *      Author: tobias
 */

#include "QuittiertZuVielHSBisSep1.h"

void QuittiertZuVielHSBisSep1::entry() {
	actions->fehlerRunter();
}

void QuittiertZuVielHSBisSep1::exit() {
}

void QuittiertZuVielHSBisSep1::WSinHSbisSep() {
}

void QuittiertZuVielHSBisSep1::MetSenAn() {
}

void QuittiertZuVielHSBisSep1::LSSepAn() {
}

void QuittiertZuVielHSBisSep1::aussortieren1(){

}

void QuittiertZuVielHSBisSep1::aussortieren2(){

}

void QuittiertZuVielHSBisSep1::aussortieren3(){

}

void QuittiertZuVielHSBisSep1::aussortieren4(){

}

void QuittiertZuVielHSBisSep1::quittiert() {
}

void QuittiertZuVielHSBisSep1::keinFehler() {
	exit();
	new (this) WartenHSBisSep1;
	entry();
}

void QuittiertZuVielHSBisSep1::fehlerCntDown(){

}

void QuittiertZuVielHSBisSep1::fehlerVerschwunden(){

}

void QuittiertZuVielHSBisSep1::eStop() {
	exit();
	actions->eStop();
	new (this) WartenHSBisSep1;
	entry();
}
