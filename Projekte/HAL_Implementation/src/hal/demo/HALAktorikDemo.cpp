/*
 * HALDemo.cpp
 *
 *  Created on: 17.10.2022
 *  Author: Tobias Thoelen
 *
 *  Eine Klasse um die Funktion des HAL zuzeigen.
 */

#include <thread>
#include <iostream>

#include "HALAktorikDemo.h"


using namespace std;


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

	//thread worker(std::bind(&Ampel::lampeSchnellBlinken, &ampel));

	//Farbe farbe = Gruen;

	//thread worker(Ampel::ampeLangsamBlinken,farbe);

	//sleep(5);
	//ampel->lampeBlinkenAus();

	//worker.join();

	/*
	ampel->lampeLangsamBlinken(Gruen);
	sleep(5);
	ampel->lampeBlinkenAus();
	sleep(5);
	 */
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

	// Um die Sensorik zu testen
	cout << "HAL Aktorik DEMO: laufband aus" << endl;
	laufband->laufbandStopAus();
	laufband->laufbandLinksAus();
	laufband->laufbandRechtsAn();
	laufband->laufbandLangsamAn();
	cout << "HAL Aktorik DEMO: laufband an" << endl;

	//ampel->lampeLangsamBlinken(Gruen);
}
