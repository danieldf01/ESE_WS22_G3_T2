/*
 * WarteSepBisLSEnde.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "WarteSepBisLSE1.h"

using namespace std;

void WarteSepBisLSE1::entry(){

}

void WarteSepBisLSE1::exit(){

}

void WarteSepBisLSE1::LsEAn(){
	entry();
	new (this) FehlerWSZuVielSepBisLSE1;
	entry();
}

void WarteSepBisLSE1::WsAufWegZuLSE(){
	new (this) WsAufWegZuLSEndeSepBisLSE1;
}

void WarteSepBisLSE1::FBM2bereit(){

}

void WarteSepBisLSE1::WsWurdeUebergeben(){

}

void WarteSepBisLSE1::quittiert(){

}

void WarteSepBisLSE1::keinFehler(){

}

void WarteSepBisLSE1::fehlerVerschwunden(){

}

void WarteSepBisLSE1::eStop(){
	actions->eStop();
}
