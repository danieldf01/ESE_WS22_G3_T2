/*
 * QuittiertZuVielHSBisSep2.cpp
 *
 *  Created on: 17.12.2022
 *      Author: tobias
 */

#include "QuittiertZuVielHSBisSep2.h"

void QuittiertZuVielHSBisSep2::entry() {
	actions->fehlerRunter();
}

void QuittiertZuVielHSBisSep2::exit() {
}

void QuittiertZuVielHSBisSep2::WSinHSbisSep() {
}

void QuittiertZuVielHSBisSep2::MetSenAn() {
}

void QuittiertZuVielHSBisSep2::LSSepAn() {
}

void QuittiertZuVielHSBisSep2::aussortieren1(){

}

void QuittiertZuVielHSBisSep2::aussortieren2(){

}

void QuittiertZuVielHSBisSep2::aussortieren3(){

}

void QuittiertZuVielHSBisSep2::quittiert() {
}

void QuittiertZuVielHSBisSep2::keinFehler() {
	new (this) WartenHSBisSep2;
}

void QuittiertZuVielHSBisSep2::fehlerCntDown(){

}

void QuittiertZuVielHSBisSep2::fehlerVerschwunden(){

}

void QuittiertZuVielHSBisSep2::eStop() {
	actions->eStop();
	new (this) WartenHSBisSep2;
}
