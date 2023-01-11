/*
 * Ampel.cpp
 *
 *  Created on: 24.10.2022
 *      Author: tobias
 */

#include "Ampel.h"

// TODO Wie soll die Ampel im Hintergrund laufen?
// TODO Wird ein weiterer Thread benötigt
// TODO Schaletet lampeAus auch das Blinken ab?
using namespace std;

Ampel::Ampel() {
	lampe = new Lampe();
}

Ampel::~Ampel() {

	// TODO Auto-generated destructor stub
}

/**
 * @parameter die Farbe Gruen, Gelb oder Rot.
 */
void Ampel::lampeBlinkenAus(Farbe farbe){
	switch(farbe){

	//GRUEN
	case 0:
		mutexGruen.lock();
		this->blinkenGruen=false;
		mutexGruen.unlock();
		break;

	//GELB
	case 1:
		mutexGelb.lock();
		this->blinkenGelb=false;
		mutexGelb.unlock();
		break;

	//ROT
	case 2:
		mutexRot.lock();
		this->blinkenRot=false;
		mutexRot.unlock();
		break;
	}
}

void Ampel::blinken(Farbe farbe, int zeit){
	switch(farbe){

	//GRUEN
	case 0:
		blinkenGruen=true; //blinken aktiv setzen
		mutexGruen.lock();
		while(blinkenGruen){
			mutexGruen.unlock();
			usleep(zeit);
			lampe->lampeGruenAn();
			usleep(zeit);
			lampe->lampeGruenAus();
			mutexGruen.lock();
		}
		mutexGruen.unlock();
		break;

	//GELB
	case 1:
		blinkenGelb=true; //blinken aktiv setzen
		mutexGelb.lock();
		while(blinkenGelb){
			mutexGelb.unlock();
			usleep(zeit);
			lampe->lampeGelbAn();
			usleep(zeit);
			lampe->lampeGelbAus();
			mutexGelb.lock();
		}
		mutexGelb.unlock();
		break;

	//ROT
	case 2:
		blinkenRot=true; //blinken aktiv setzen
		zeitRot=zeit;
		mutexRot.lock();
		while(blinkenRot){
			mutexRot.unlock();
			usleep(zeitRot);
			lampe->lampeRotAn();
			usleep(zeitRot);
			lampe->lampeRotAus();
			mutexRot.lock();
		}
		mutexRot.unlock();
		break;
	}
}


AmpelWrapper::AmpelWrapper(Ampel &ampel): ampel(ampel){}

void AmpelWrapper::operator ()(Farbe farbe,int zeit){
	ampel.blinken(farbe,zeit);

}

