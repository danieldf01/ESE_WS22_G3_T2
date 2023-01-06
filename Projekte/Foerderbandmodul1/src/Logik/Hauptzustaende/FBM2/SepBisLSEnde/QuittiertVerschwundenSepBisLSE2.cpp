/*
 * QuittiertWSVerschwunden.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "QuittiertVerschwundenSepBisLSE2.h"

void QuittiertVerschwundenSepBisLSE2::entry(){
	actions->fehlerRunter();
}

void QuittiertVerschwundenSepBisLSE2::exit(){

}

void QuittiertVerschwundenSepBisLSE2::LsEAn(){

}

void QuittiertVerschwundenSepBisLSE2::LsEAus() {

}

void QuittiertVerschwundenSepBisLSE2::WsPassieren(){

}

void QuittiertVerschwundenSepBisLSE2::WeicheSchliessen(){

}

void QuittiertVerschwundenSepBisLSE2::quittiert(){

}

void QuittiertVerschwundenSepBisLSE2::keinFehler(){
	exit();
	actions->sendFBM2Bereit();
	entry();
}

void QuittiertVerschwundenSepBisLSE2::fehlerVerschwunden(){

}

void QuittiertVerschwundenSepBisLSE2::eStop(){
	actions->eStop();
	new (this) WarteSepBisLSE2;
}
