/*
 * Werkstueck.cpp
 *
 *  Created on: Dec 11, 2022
 *      Author: bardi
 */

#include "Werkstueck.h"

Werkstueck::Werkstueck(int iD, unsigned int timestamp) {
	this->iD= iD;
	this->timestamp = timestamp;
}

Werkstueck::~Werkstueck() {

}

int Werkstueck::getiD(){
	return this->iD;
}

unsigned int Werkstueck::getTimestamp(){
	return this->timestamp;
}

void Werkstueck::setTimestamp(unsigned int timestamp){
	this->timestamp=timestamp;
}

WsTyp Werkstueck::getWsTyp(){
	return this->wsTyp;
}

void Werkstueck::setWsTyp(WsTyp typ){
	this->wsTyp=typ;
}

double Werkstueck::getMittlereHoehe(){
	return this->mittlereHoehe;
}

void Werkstueck::setMittlereHoehe(double hoehe){
	this->mittlereHoehe=hoehe;
}

double Werkstueck::getHoehenmesswert(){
	return this->hoehenmesswert;
}

void Werkstueck::setHoehenmesswert(double messwert){
	this->hoehenmesswert=messwert;
}

bool Werkstueck::istUeberschlagen(){
	return this->ueberschlagen;
}

void Werkstueck::setUeberschlagen(){
	this->ueberschlagen=true;
}
