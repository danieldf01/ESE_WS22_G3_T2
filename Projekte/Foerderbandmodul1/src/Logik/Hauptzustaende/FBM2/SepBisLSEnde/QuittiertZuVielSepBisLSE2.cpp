/*
 * QuittiertWSZuVielSepBisLSEnde.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "QuittiertZuVielSepBisLSE2.h"

void QuittiertZuVielSepBisLSE2::entry(){
	actions->fehlerRunter();
}

void QuittiertZuVielSepBisLSE2::exit(){

}

void QuittiertZuVielSepBisLSE2::LsEAn(){

}

void QuittiertZuVielSepBisLSE2::LsEAus() {

}

void QuittiertZuVielSepBisLSE2::WsPassieren(){

}

void QuittiertZuVielSepBisLSE2::WeicheSchliessen(){

}

void QuittiertZuVielSepBisLSE2::FBM2bereit(){

}

void QuittiertZuVielSepBisLSE2::WsWurdeUebergeben(){

}

void QuittiertZuVielSepBisLSE2::quittiert(){

}

void QuittiertZuVielSepBisLSE2::keinFehler(){
	exit();
	new (this) WarteSepBisLSE2;
	entry();
}

void QuittiertZuVielSepBisLSE2::fehlerVerschwunden(){

}

void QuittiertZuVielSepBisLSE2::eStop(){
	actions->eStop();
	new (this) WarteSepBisLSE2;
}
