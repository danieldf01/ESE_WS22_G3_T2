/*
 * WsAufWegZuLSEndeSepBisLSE1.cpp
 *
 *  Created on: 22.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "WsAufWegZuLSEndeSepBisLSE1.h"

using namespace std;

void WsAufWegZuLSEndeSepBisLSE1::entry(){

}

void WsAufWegZuLSEndeSepBisLSE1::exit(){

}

void WsAufWegZuLSEndeSepBisLSE1::LsEAn(){
	exit();
	actions->deleteTimerVerschwunden();

	//WS zu frueh angekommen?
	if(zeitmanager->getTime() < (1500 + wsListen->ws_list_sep_bis_lsende.front().getTimestamp())){// TODO Timer define
		new (this) FehlerWSZuFruehSepBisLSE1;
	} else{
		actions->stopHoch();
		actions->FBM1bereit();
		new (this) WartenFreiwerdenFBM2;
	}
	entry();
}

void WsAufWegZuLSEndeSepBisLSE1::WsAufWegZuLSE(){

}

void WsAufWegZuLSEndeSepBisLSE1::FBM2bereit(){

}

void WsAufWegZuLSEndeSepBisLSE1::WsWurdeUebergeben(){

}

void WsAufWegZuLSEndeSepBisLSE1::quittiert(){

}

void WsAufWegZuLSEndeSepBisLSE1::keinFehler(){

}

void WsAufWegZuLSEndeSepBisLSE1::fehlerVerschwunden(){
	exit();
	new (this) FehlerWSVerschwundenSepBisLSE1;
	entry();
}

void WsAufWegZuLSEndeSepBisLSE1::eStop(){
	actions->eStop();
	new (this) WarteSepBisLSE1;
}
