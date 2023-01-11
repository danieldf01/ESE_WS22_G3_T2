/*
 * WartenAufFreiwerdenVonFBM2.cpp
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#include "WartenFreiwerdenFBM2.h"

void WartenFreiwerdenFBM2::entry(){

}

void WartenFreiwerdenFBM2::exit(){

}

void WartenFreiwerdenFBM2::LsEAn(){

}

void WartenFreiwerdenFBM2::WsAufWegZuLSE(){

}

void WartenFreiwerdenFBM2::FBM2bereit(){
	exit();
	actions->FBM1WsLosgeschickt();
	actions->stopRunter();
	new (this) UebergabeAnFBM2;
	entry();
}

void WartenFreiwerdenFBM2::WsWurdeUebergeben(){

}

void WartenFreiwerdenFBM2::quittiert(){

}

void WartenFreiwerdenFBM2::keinFehler(){

}

void WartenFreiwerdenFBM2::fehlerVerschwunden(){

}

void WartenFreiwerdenFBM2::eStop(){
	actions->eStop();
	new (this) WarteSepBisLSE1;
}
