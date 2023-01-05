/*
 * Watchdog.cpp
 *
 *  Created on: 13.11.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "Watchdog.h"

//global variables
//Timer sendTimer
//Timer receiveTimer
//CommunicationDispatcher dispatcher

Watchdog::Watchdog() {
	// TODO Auto-generated constructor stub
	//create objects for global var.
}

Watchdog::~Watchdog() {
	// TODO Auto-generated destructor stub
}

void Watchdog::notify(){
	//TODO: receiveTimer resetten
}

//brauchen timer function, die sendSignal() alle 200ms aufruft
void Watchdog::sendSignal(){
	//TODO: Signal an anderen Watchdog senden
	//dispatcher->sendSignal();
}

void Watchdog::eStopp(){
	//TODO: E-Stopp-Signal senden
	//dispatcher->receiveSignal();
}

