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
 *
 * @parameter die Farbe Gruen, Gelb oder Rot.
 */
//void Ampel::lampeSchnellBlinken(Farbe farbe) {
//	switch(farbe){
//					case 0:
//						this->zeitGruen=HALBESEKUNDE;
//						break;
//					case 1:
//						this->zeitGelb=HALBESEKUNDE;
//						break;
//					case 2:
//						this->zeitRot=HALBESEKUNDE;
//						break;
//				}
//}
//
///**
// * @parameter die Farbe Gruen, Gelb oder Rot.
// */
//void Ampel::lampeLangsamBlinken(Farbe farbe) {
//	switch(farbe){
//					case 0:
//						this->zeitGruen=SEKUNDE;
//						break;
//					case 1:
//						this->zeitGelb=SEKUNDE;
//						break;
//					case 2:
//						this->zeitRot=SEKUNDE;
//						break;
//				}
//}

//void Ampel::lampeBlinkenAus(Farbe farbe){
//	switch(farbe){
//				case 0:
//					this->blinkenGruen=false;
//					break;
//				case 1:
//					this->blinkenGelb=false;
//					break;
//				case 2:
//					this->blinkenRot=false;
//					break;
//			}
//}

void Ampel::lampeBlinkenAus(Farbe farbe){
	switch(farbe){
				case 0:
					this->blinkenGruen=false;
					break;
				case 1:
					this->blinkenGelb=false;
					break;
				case 2:
					this->blinkenRot=false;
					break;
			}
}
void Ampel::blinken(Farbe farbe,int zeit){

	switch(farbe){
				case 0:
					mutexGruen.lock();	//blinken für andere threads sperren
					blinkenGruen=true; //blinken aktiv setzen
					while(blinkenGruen){
								usleep(zeit);
								lampe->lampeAn(farbe);
								usleep(zeit);
								lampe->lampeAus(farbe);
						}
						mutexGruen.unlock();
					break;

				case 1:
					mutexGelb.lock();	//blinken für andere threads sperren
					blinkenGelb=true; //blinken aktiv setzen
					while(blinkenGelb){
								usleep(zeit);
								lampe->lampeAn(farbe);
								usleep(zeit);
								lampe->lampeAus(farbe);
						}
						mutexGelb.unlock();
					break;

				case 2:
					mutexRot.lock();	//blinken für andere threads sperren
					blinkenRot=true; //blinken aktiv setzen
					while(blinkenRot){
								usleep(zeit);
								lampe->lampeAn(farbe);
								usleep(zeit);
								lampe->lampeAus(farbe);
						}
						mutexRot.unlock();
					break;
			}
}


AmpelWrapper::AmpelWrapper(Ampel &ampel): ampel(ampel){}

void AmpelWrapper::operator ()(Farbe farbe,int zeit){

	ampel.blinken(farbe,zeit);

}

