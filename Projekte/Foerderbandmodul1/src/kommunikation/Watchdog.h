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
	//sendTimer
	timer_t sTimerID;
	struct sigevent sTimerEvent;
	struct itimerspec sTimer;

	//EStoppTimer
	timer_t esTimerID;
	struct sigevent esTimerEvent;
	struct itimerspec esTimer;
public:
	Watchdog(int);
	virtual ~Watchdog();
	void notify();
	void initESTimer();
	void initSTimer();
	void stopTimer();
};

#endif /* KOMMUNIKATION_WATCHDOG_H_ */
