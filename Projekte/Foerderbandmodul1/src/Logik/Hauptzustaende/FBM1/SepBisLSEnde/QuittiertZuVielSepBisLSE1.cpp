/*
 * QuittiertWSZuVielSepBisLSEnde.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "QuittiertZuVielSepBisLSE1.h"

void QuittiertZuVielSepBisLSE1::entry(){
	actions->fehlerRunter();
}

void QuittiertZuVielSepBisLSE1::exit(){

}

void QuittiertZuVielSepBisLSE1::LsEAn(){

}

void QuittiertZuVielSepBisLSE1::WsPassieren(){

}

void QuittiertZuVielSepBisLSE1::WeicheSchliessen(){

}

void QuittiertZuVielSepBisLSE1::FBM2bereit(){

}

void QuittiertZuVielSepBisLSE1::WsWurdeUebergeben(){

}

void QuittiertZuVielSepBisLSE1::quittiert(){

}

void QuittiertZuVielSepBisLSE1::keinFehler(){
	exit();
	new (this) WarteSepBisLSE1;
	entry();
}

void QuittiertZuVielSepBisLSE1::fehlerVerschwunden(){

}

void QuittiertZuVielSepBisLSE1::eStop(){
	actions->eStop();
	new (this) WarteSepBisLSE1;
}
