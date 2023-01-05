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

Ampel::Ampel() {
	this->lampe = new Lampe();
}

Ampel::~Ampel() {
	// TODO Auto-generated destructor stub
}

/**
 *
 * @parameter die Farbe Gruen, Gelb oder Rot.
 */
void Ampel::lampeSchnellBlinken(Farbe farbe) {
	usleep(HALBESEKUNDE);
	lampeAn(farbe);
	usleep(HALBESEKUNDE);
	lampeAus(farbe);

}

/**
 * @parameter die Farbe Gruen, Gelb oder Rot.
 */
void Ampel::lampeLangsamBlinken(Farbe farbe) {
	usleep(SEKUNDE);
	lampeAn(farbe);
	usleep(SEKUNDE);
	lampeAus(farbe);
}

/**
 * @parameter die Farbe Gruen, Gelb oder Rot.
 */
void Ampel::lampeAn(Farbe farbe) {
	switch(farbe){
			case 0:
				lampe->lampeGruenAn();
				break;
			case 1:
				lampe->lampeGelbAn();
				break;
			case 2:
				lampe->lampeRotAn();
				break;
		}
}

/**
 * @parameter die Farbe Gruen, Gelb oder Rot.
 */
void Ampel::lampeAus(Farbe farbe) {
	switch(farbe){
			case 0:
				lampe->lampeGruenAus();
				break;
			case 1:
				lampe->lampeGelbAus();
				break;
			case 2:
				lampe->lampeRotAus();
				break;
		}
}
