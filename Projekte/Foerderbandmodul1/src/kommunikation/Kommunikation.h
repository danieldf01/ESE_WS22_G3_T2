/*
 * Kommunikation.h
 *
 *  Created on: 25.11.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef KOMMUNIKATION_KOMMUNIKATION_H_
#define KOMMUNIKATION_KOMMUNIKATION_H_

#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <thread>
#include <sys/dispatch.h>
#include <mutex>

#include "Watchdog.h"
#include "../dispatcher/QnetHandler.h"
#include "../dispatcher/OutputDispatcher.h"
#include "../Logik/Defines.h"

class Kommunikation {
private:
	Watchdog *watchdog;
	QnetHandler *qnetHandler;
	OutputDispatcher *outputDispatcher;
	name_attach_t *attach;
	int coid_kom_s;
	int coid_indis;

	//TODO funktioniert das so?
	std::mutex watchdogM;
	bool watchdogES;
public:
	Kommunikation(OutputDispatcher &oD);
	virtual ~Kommunikation();
	void init();
	void receiveSignal();
	void pulseFBM1(int);
	void pulseFBM2(int);
	void sendPulse(int, int, int);
};

#endif /* KOMMUNIKATION_KOMMUNIKATION_H_ */
