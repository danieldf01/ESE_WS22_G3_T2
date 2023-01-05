/*
 * BlinkerThread.cpp
 *
 *  Created on: 13.11.2022
 *      Author: User
 */

#include "BlinkerThread.h"

using namespace std;

BlinkerThread::BlinkerThread() {
	farbe = Farbe::Gruen;
	zeit = HALBESEKUNDE;
	blinkenAktiv=true;
	lampe = new Lampe();
}

BlinkerThread::~BlinkerThread() {
	// TODO Auto-generated destructor stub
}

void BlinkerThread::blinken(){
	while(blinkenAktiv){
			usleep(zeit);
			lampe->lampeAn(farbe);
			usleep(zeit);
			lampe->lampeAus(farbe);
	}

	//blinken wieder aktiv setzen
	blinkenAktiv=true;
}


