/*
 * WartenPassieren.cpp
 *
 *  Created on: 07.01.2023
 *      Author: Daniel Drefs Fernandes
 */

#include "WartenPassieren.h"

using namespace std;

void WartenPassieren::entry(){

}

void WartenPassieren::exit(){

}

void WartenPassieren::WsPassieren(){
//	cout << "WarteSepBisLSE1::WsPassieren" << endl;
	if(wsListen->ws_list_passieren.size() > 0){
		if(!konfig->get_value_of(Konfi_Codes::FBM1_AUSWERFER_TRUE)){
			actions->seperatorAn();
			new (this) WeicheGeoeffnetPassieren;
		} else{
			actions->WsAufWegZuLSE();
			// Ist schon im richtigen State
		}
	}
}

void WartenPassieren::WeicheSchliessen(){

}

void WartenPassieren::eStop(){
	actions->eStop();
}
