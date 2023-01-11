/*
 * UebergabeAnFBM2.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "UebergabeAnFBM2.h"

void UebergabeAnFBM2::entry(){

}

void UebergabeAnFBM2::exit(){

}

void UebergabeAnFBM2::LsEAn(){

}

void UebergabeAnFBM2::WsAufWegZuLSE(){

}

void UebergabeAnFBM2::FBM2bereit(){

}

void UebergabeAnFBM2::WsWurdeUebergeben(){
	exit();
	actions->FBM1WsUebergeben();
	if(wsListen->ws_list_sep_bis_lsende.size() > 0){
		new (this) WsAufWegZuLSEndeSepBisLSE1;
	} else if(wsListen->ws_list_sep_bis_lsende.size() <= 0){
		new (this) WarteSepBisLSE1;
	}
	entry();
}

void UebergabeAnFBM2::quittiert(){

}

void UebergabeAnFBM2::keinFehler(){

}

void UebergabeAnFBM2::fehlerVerschwunden(){

}

void UebergabeAnFBM2::eStop(){
	actions->eStop();
	new (this) WarteSepBisLSE1;
}
