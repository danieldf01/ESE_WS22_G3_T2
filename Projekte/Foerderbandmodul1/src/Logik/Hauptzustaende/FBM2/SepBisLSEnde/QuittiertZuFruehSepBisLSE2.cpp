/*
 * QuittiertWSZuFrueh.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "QuittiertZuFruehSepBisLSE2.h"

void QuittiertZuFruehSepBisLSE2::entry(){
	actions->fehlerRunter();
}

void QuittiertZuFruehSepBisLSE2::exit(){

}

void QuittiertZuFruehSepBisLSE2::LsEAn(){

}

void QuittiertZuFruehSepBisLSE2::WsPassieren(){

}

void QuittiertZuFruehSepBisLSE2::WeicheSchliessen(){

}

void QuittiertZuFruehSepBisLSE2::FBM2bereit(){

}

void QuittiertZuFruehSepBisLSE2::WsWurdeUebergeben(){

}

void QuittiertZuFruehSepBisLSE2::quittiert(){

}

void QuittiertZuFruehSepBisLSE2::keinFehler(){
	exit();
	new (this) WsAufWegZuLSEndeSepBisLSE2;
	entry();
}

void QuittiertZuFruehSepBisLSE2::fehlerVerschwunden(){

}

void QuittiertZuFruehSepBisLSE2::eStop(){
	actions->eStop();
	new (this) WarteSepBisLSE2;
}
