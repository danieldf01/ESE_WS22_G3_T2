/*
 * QuittiertWSVerschwunden.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "QuittiertVerschwundenSepBisLSE1.h"

void QuittiertVerschwundenSepBisLSE1::entry(){
	actions->fehlerRunter();
}

void QuittiertVerschwundenSepBisLSE1::exit(){

}

void QuittiertVerschwundenSepBisLSE1::LsEAn(){

}

void QuittiertVerschwundenSepBisLSE1::WsPassieren(){

}

void QuittiertVerschwundenSepBisLSE1::WeicheSchliessen(){

}

void QuittiertVerschwundenSepBisLSE1::FBM2bereit(){

}

void QuittiertVerschwundenSepBisLSE1::WsWurdeUebergeben(){

}

void QuittiertVerschwundenSepBisLSE1::quittiert(){

}

void QuittiertVerschwundenSepBisLSE1::keinFehler(){
	exit();
	if(wsListen->ws_list_passieren.size() > 0){
		if(!konfig->get_value_of(Konfi_Codes::FBM1_AUSWERFER_TRUE)){
			actions->seperatorAn();
			new (this) WeicheGeoeffnetSepBisLSE1;
		} else{
			new (this) WsAufWegZuLSEndeSepBisLSE1;
		}
	} else if(wsListen->ws_list_passieren.size() <= 0){
		new (this) WarteSepBisLSE1;
	}
	entry();
}

void QuittiertVerschwundenSepBisLSE1::fehlerVerschwunden(){

}

void QuittiertVerschwundenSepBisLSE1::eStop(){
	actions->eStop();
	new (this) WarteSepBisLSE1;
}
