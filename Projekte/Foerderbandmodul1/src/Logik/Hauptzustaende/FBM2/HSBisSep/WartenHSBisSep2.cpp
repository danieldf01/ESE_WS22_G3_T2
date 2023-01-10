/*
 * WartenHSBisSep2.cpp
 *
 *  Created on: 17.12.2022
 *      Author: tobias
 */

#include "WartenHSBisSep2.h"

void WartenHSBisSep2::entry() {
}

void WartenHSBisSep2::exit() {
}

void WartenHSBisSep2::WSinHSbisSep() {
	new (this) WSAufWegZumSep2;
}

void WartenHSBisSep2::MetSenAn() {

}

void WartenHSBisSep2::LSSepAn() {
	new (this) FehlerWSZuVielHSBisSep2;
	entry();
}

void WartenHSBisSep2::aussortieren1(){

}

void WartenHSBisSep2::aussortieren2(){

}

void WartenHSBisSep2::aussortieren3(){

}

void WartenHSBisSep2::quittiert() {
}

void WartenHSBisSep2::keinFehler() {
}

void WartenHSBisSep2::fehlerCntDown(){

}

void WartenHSBisSep2::fehlerVerschwunden(){

}

void WartenHSBisSep2::eStop() {
	actions->eStop();
}
