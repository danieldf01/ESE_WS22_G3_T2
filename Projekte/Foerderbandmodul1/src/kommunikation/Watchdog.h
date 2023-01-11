/*
 * Watchdog.h
 *
 *  Created on: 25.11.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef KOMMUNIKATION_WATCHDOG_H_
#define KOMMUNIKATION_WATCHDOG_H_

#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <thread>
#include <sys/dispatch.h>
#include <sys/dispatch.h>

#include "../Logik/Defines.h"
#include "../dispatcher/QnetHandler.h"

#define SERVER_KOM_MASTER "KommunikationMaster"

class Watchdog {
private:
	//connection
	QnetHandler *qnetHandler;
	int coid_master;
	int chid_master;

	//timer fuer sicherheit
	timer_t timerID;
	struct sigevent timerEvent;
	struct itimerspec timer;
public:
	Watchdog(int);
	virtual ~Watchdog();
	void notify();
	void initTimer();
};

#endif /* KOMMUNIKATION_WATCHDOG_H_ */
