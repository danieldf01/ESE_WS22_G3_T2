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

void WarteSepBisLSE1::WsPassieren(){
	if(wsListen->ws_list_passieren.size() > 0){
		exit();
		if(!konfig->get_value_of(Konfi_Codes::FBM1_AUSWERFER_TRUE)){
			actions->seperatorAn();
			new (this) WeicheGeoeffnetSepBisLSE1;
		} else{
			new (this) WsAufWegZuLSEndeSepBisLSE1;
		}
		entry();
	}
}

void WarteSepBisLSE1::WeicheSchliessen(){

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
