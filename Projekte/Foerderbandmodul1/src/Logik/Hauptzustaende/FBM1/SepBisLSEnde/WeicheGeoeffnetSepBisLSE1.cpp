/*
 * WeicheGeoeffnetSepBisLSE1.cpp
 *
 *  Created on: 22.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "WeicheGeoeffnetSepBisLSE1.h"

void WeicheGeoeffnetSepBisLSE1::entry(){

}

void WeicheGeoeffnetSepBisLSE1::exit(){

}

void WeicheGeoeffnetSepBisLSE1::LsEAn(){

}

void WeicheGeoeffnetSepBisLSE1::WsPassieren(){

}

void WeicheGeoeffnetSepBisLSE1::WeicheSchliessen(){
	exit();
	actions->seperatorAus();
	new (this) WsAufWegZuLSEndeSepBisLSE1;
	entry();
}

void WeicheGeoeffnetSepBisLSE1::FBM2bereit(){

}

void WeicheGeoeffnetSepBisLSE1::WsWurdeUebergeben(){

}

void WeicheGeoeffnetSepBisLSE1::quittiert(){

}

void WeicheGeoeffnetSepBisLSE1::keinFehler(){

}

void WeicheGeoeffnetSepBisLSE1::fehlerVerschwunden(){

}

void WeicheGeoeffnetSepBisLSE1::eStop(){
	actions->eStop();
	new (this) WarteSepBisLSE1;
}
