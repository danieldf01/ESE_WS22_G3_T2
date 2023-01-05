/*
 * HALDemo.cpp
 *
 *  Created on: 17.10.2022
 *  Author: Tobias Thoelen
 *
 *  Eine Klasse um die Funktion des HAL zuzeigen.
 */
#include "DemoHAL.h"

//TODO bug gefunden irgendwie führt das usleep dazu das es keine Ausgabe gab?

HALAktorikDemo::HALAktorikDemo() {
	this->lampe = new Lampe();
	this->bedienpanel = new Bedienpanel();
	this->sortierer = new Seperator();
	this->laufband =  new Laufband();
	this->ampel = new Ampel();
}

HALAktorikDemo::~HALAktorikDemo() {
//TODO DELETE
}

void HALAktorikDemo::runDemo() {


	/*
	lampe->lampeGelbAn();
	sleep(1);
	lampe->lampeGelbAus();
	sleep(1);
	lampe->lampeGruenAn();
	sleep(1);
	lampe->lampeGruenAus();
	sleep(1);
	lampe->lampeRotAn();
	sleep(1);
	lampe->lampeRotAus();
	sleep(1);
	*/

	/*
	sortierer->sortiererAusfahren();
	sleep(1);
	sortierer->sortiererEinfahren();
	sleep(1);
	*/

	/*
	bedienpanel->ledStartAn();
	bedienpanel->ledStartAus();
	*/

	/*
	sleep(1);
	bedienpanel->ledStartAn();
	sleep(1);
	bedienpanel->ledStartAus();
	sleep(1);
	bedienpanel->ledResetAn();
	sleep(1);
	bedienpanel->ledResetAus();
	sleep(1);
	bedienpanel->signalleuchteQ1An();
	sleep(1);
	bedienpanel->signalleuchteQ1Aus();
	sleep(1);
	bedienpanel->signalleuchteQ2An();
	sleep(1);
	bedienpanel->signalleuchteQ2Aus();
	*/

	/*
	sleep(1);
	laufband->laufbandLinksAn();
	sleep(1);
	laufband->laufbandLinksAus();
	sleep(1);
	laufband->laufbandRechtsAn();
	sleep(1);
	laufband->laufbandLangsamAn();
	sleep(1);
	laufband->laufbandLangsamAus();
	sleep(1);
	laufband->laufbandRechtsAus();
	sleep(1);
	laufband->laufbandStopAn();
	sleep(1);
	laufband->laufbandStopAus();
	sleep(1);
	*/

	//ampel->lampeLangsamBlinken(Gruen);

	//ampel->lampeLangsamBlinken(Rot);
}
