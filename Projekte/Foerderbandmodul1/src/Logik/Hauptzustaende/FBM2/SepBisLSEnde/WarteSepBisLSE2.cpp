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
	new (this) FehlerWSZuVielSepBisLSE2;
	entry();
}

void WarteSepBisLSE2::LsEAus() {

}

void WarteSepBisLSE2::WsPassieren(){
//	cout << "WarteSepBisLSE2 recv:WsPassieren" << endl;
	if (!konfig->get_value_of(Konfi_Codes::FBM2_AUSWERFER_TRUE)) {
//		cout << "WarteSepBisLSE2 isWeiche" << endl;
		actions->seperatorAn();
		new (this) WeicheGeoeffnetSepBisLSE2;
	} else {
//		cout << "WarteSepBisLSE2 isAuswerfer" << endl;
		new (this) WsAufWegZuLSEndeSepBisLSE2;
	}
}

void WarteSepBisLSE2::WeicheSchliessen(){

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
