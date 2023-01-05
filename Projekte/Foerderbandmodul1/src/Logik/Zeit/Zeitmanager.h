/*
 * Zeitmanager.h
 *
 *  Created on: 09.12.2022
 *      Author: Tobias Thoelen
 */

#ifndef LOGIK_ZEITMANAGER_H_
#define LOGIK_ZEITMANAGER_H_

#include <iostream>
#include <signal.h>
#include <thread>
#include <sys/dispatch.h>
#include <sys/neutrino.h>
#include <unistd.h>
#include <list>
#include <tuple>
#include "../../dispatcher/QnetHandler.h"


#define  TIMER_INTERVAL 10000000 //in nanoSek

class Zeitmanager {
private:
	unsigned int zeit; //zeit in ms
	unsigned int schnell;
	unsigned int langsam;
	unsigned int currentSpeed;
	int chid;
	int coid;
	int pulse_code;

	std::list<std::tuple<unsigned int, std::tuple<int, int>>> lmessungen;

	void startTimerPeriodisch(int intervalNanoSek, int chid);
public:
	Zeitmanager(unsigned int schnell, unsigned int langsam, int chid, int pulse_code);
	virtual ~Zeitmanager();
	void threadStartZeit();
	unsigned int getTime();
	void setTimerSpeedLangsam();
	void setTimerSpeedSchnell();
	void setTimerSpeedStop();
	void startMessung(unsigned int millisek, int pulse_payload, int wsID);
	void clearLists();
	void deleteTimer(int wsID);

};

#endif /* LOGIK_ZEITMANAGER_H_ */
