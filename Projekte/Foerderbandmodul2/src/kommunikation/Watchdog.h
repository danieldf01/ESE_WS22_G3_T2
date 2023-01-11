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
#include <time.h>
#include <sys/siginfo.h>
#include <sys/dispatch.h>
#include <sys/neutrino.h>
#include <sys/iomsg.h>

#define SERVER_KOM_SLAVE "KommunikationSlave"

#define CODE_FBM_2		_PULSE_CODE_MINAVAIL + 2
#define WATCHDOG_NOTIF	50
#define WATCHDOG_ESTOP	51
#define WATCHDOG_SEND_NOTIF 666

class Watchdog {
private:
	//connection
	int chid_slave;
	int coid_slave;

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
