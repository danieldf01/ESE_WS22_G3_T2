/*
 * watchdog.h
 *
 *  Created on: 11.01.2023
 *      Author: m
 */

#ifndef KOMMUNIKATION_WATCHDOG_WATCHDOG_H_
#define KOMMUNIKATION_WATCHDOG_WATCHDOG_H_

#include "../../dispatcher/OutputDispatcher.h"
#include "../../Logik/Defines.h"


#define  TIMER_INTERVAL 10000000 //in nanoSek

class Watchdog {
public:
	Watchdog(OutputDispatcher &dispatcher);
	virtual ~Watchdog();
	unsigned int zeit;
	OutputDispatcher *outputDispatcher;
	name_attach_t *attach;
	QnetHandler *qnetHandler;
	int coid_kommunikation;
	void startTimerPeriodisch(int intervalNanoSek, int chid);
	void threadWatchdog();
};



#endif /* KOMMUNIKATION_WATCHDOG_WATCHDOG_H_ */
