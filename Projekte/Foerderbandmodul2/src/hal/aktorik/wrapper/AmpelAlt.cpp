///*
// * Ampel.cpp
// *
// *  Created on: 24.10.2022
// *      Author: tobias
// */
//
//#include "Ampel.h"
//
//// TODO Wie soll die Ampel im Hintergrund laufen?
//// TODO Wird ein weiterer Thread benötigt
//// TODO Schaletet lampeAus auch das Blinken ab?
//using namespace std;
//
//Ampel::Ampel() {
//	this->blinker = BlinkerThread();
//}
//
//Ampel::~Ampel() {
//
//	// TODO Auto-generated destructor stub
//}
//
///**
// *
// * @parameter die Farbe Gruen, Gelb oder Rot.
// */
//void Ampel::lampeSchnellBlinken(Farbe farbe) {
//	blinker.farbe = farbe;
//	blinker.zeit = HALBESEKUNDE;
//	blinker.blinken();
//}
//
///**
// * @parameter die Farbe Gruen, Gelb oder Rot.
// */
//void Ampel::lampeLangsamBlinken(Farbe farbe) {
//	blinker.farbe = farbe;
//	blinker.zeit = SEKUNDE;
//	blinker.blinken();
//}
//
//void Ampel::lampeBlinkenAus(){
//	blinker.blinkenAktiv=false;
//}
//
//AmpelWrapper::AmpelWrapper(Ampel &ampel): ampel(ampel){}
//
//void AmpelWrapper::operator ()(Farbe farbe){
//
//	ampel.lampeLangsamBlinken(farbe);
//
//}
//
