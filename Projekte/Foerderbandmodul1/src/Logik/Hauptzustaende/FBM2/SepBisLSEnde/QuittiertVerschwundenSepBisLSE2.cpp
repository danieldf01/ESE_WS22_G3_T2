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

void QuittiertVerschwundenSepBisLSE2::WsPassieren(){

}

void QuittiertVerschwundenSepBisLSE2::WeicheSchliessen(){

}

void QuittiertVerschwundenSepBisLSE2::FBM2bereit(){

}

void QuittiertVerschwundenSepBisLSE2::WsWurdeUebergeben(){

}

void QuittiertVerschwundenSepBisLSE2::quittiert(){

}

void QuittiertVerschwundenSepBisLSE2::keinFehler(){
	exit();
	if(wsListen->ws_list_passieren.size() > 0){
		if(!konfig->get_value_of(Konfi_Codes::FBM1_AUSWERFER_TRUE)){
			actions->seperatorAn();
			new (this) WeicheGeoeffnetSepBisLSE2;
		} else{
			new (this) WsAufWegZuLSEndeSepBisLSE2;
		}
	} else if(wsListen->ws_list_passieren.size() <= 0){
		new (this) WarteSepBisLSE2;
	}
	entry();
}

void QuittiertVerschwundenSepBisLSE2::fehlerVerschwunden(){

}

void QuittiertVerschwundenSepBisLSE2::eStop(){
	actions->eStop();
	new (this) WarteSepBisLSE2;
}
