/*
 * WeicheGeoeffnetSepBisLSE2.cpp
 *
 *  Created on: 22.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "WeicheGeoeffnetSepBisLSE2.h"

void WeicheGeoeffnetSepBisLSE2::entry(){

}

void WeicheGeoeffnetSepBisLSE2::exit(){

}

void WeicheGeoeffnetSepBisLSE2::LsEAn(){

}

void WeicheGeoeffnetSepBisLSE2::LsEAus() {

}

void WeicheGeoeffnetSepBisLSE2::WsPassieren(){

}

void WeicheGeoeffnetSepBisLSE2::WeicheSchliessen(){
	exit();
	actions->seperatorAus();
	new (this) WsAufWegZuLSEndeSepBisLSE2;
	entry();
}

void WeicheGeoeffnetSepBisLSE2::FBM2bereit(){

}

void WeicheGeoeffnetSepBisLSE2::WsWurdeUebergeben(){

}

void WeicheGeoeffnetSepBisLSE2::quittiert(){

}

void WeicheGeoeffnetSepBisLSE2::keinFehler(){

}

void WeicheGeoeffnetSepBisLSE2::fehlerVerschwunden(){

}

void WeicheGeoeffnetSepBisLSE2::eStop(){
	actions->eStop();
	new (this) WarteSepBisLSE2;
}
