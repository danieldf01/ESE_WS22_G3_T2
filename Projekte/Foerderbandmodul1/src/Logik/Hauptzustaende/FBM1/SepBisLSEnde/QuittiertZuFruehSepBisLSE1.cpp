/*
 * QuittiertWSZuFrueh.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "QuittiertZuFruehSepBisLSE1.h"

void QuittiertZuFruehSepBisLSE1::entry(){
	actions->fehlerRunter();
}

void QuittiertZuFruehSepBisLSE1::exit(){

}

void QuittiertZuFruehSepBisLSE1::LsEAn(){

}

void QuittiertZuFruehSepBisLSE1::WsAufWegZuLSE(){

}

void QuittiertZuFruehSepBisLSE1::FBM2bereit(){

}

void QuittiertZuFruehSepBisLSE1::WsWurdeUebergeben(){

}

void QuittiertZuFruehSepBisLSE1::quittiert(){

}

void QuittiertZuFruehSepBisLSE1::keinFehler(){
	exit();
	new (this) WsAufWegZuLSEndeSepBisLSE1;
	entry();
}

void QuittiertZuFruehSepBisLSE1::fehlerVerschwunden(){

}

void QuittiertZuFruehSepBisLSE1::eStop(){
	actions->eStop();
	new (this) WarteSepBisLSE1;
}
