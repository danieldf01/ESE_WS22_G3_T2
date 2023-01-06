/*
 * WarteSepBisLSEnde.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "WarteSepBisLSE2.h"

using namespace std;

void WarteSepBisLSE2::entry(){

}

void WarteSepBisLSE2::exit(){

}

void WarteSepBisLSE2::LsEAn(){
	entry();
	new (this) FehlerWSZuVielSepBisLSE2;
	entry();
}

void WarteSepBisLSE2::WsPassieren(){
	if(wsListen->ws_list_passieren.size() > 0){
		exit();
		if(!konfig->get_value_of(Konfi_Codes::FBM1_AUSWERFER_TRUE)){
			actions->seperatorAn();
			new (this) WeicheGeoeffnetSepBisLSE2;
		} else{
			new (this) WsAufWegZuLSEndeSepBisLSE2;
		}
		entry();
	}
}

void WarteSepBisLSE2::WeicheSchliessen(){

}

void WarteSepBisLSE2::FBM2bereit(){

}

void WarteSepBisLSE2::WsWurdeUebergeben(){

}

void WarteSepBisLSE2::quittiert(){

}

void WarteSepBisLSE2::keinFehler(){

}

void WarteSepBisLSE2::fehlerVerschwunden(){

}

void WarteSepBisLSE2::eStop(){
	actions->eStop();
}
