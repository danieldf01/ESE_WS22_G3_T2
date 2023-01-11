/*
 * Watchdog.cpp
 *
 *  Created on: 25.11.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "Watchdog.h"

using namespace std;
Watchdog::Watchdog(int iD_master) {
	//initialize connection
	qnetHandler = new QnetHandler();
	chid_master = iD_master;
	coid_master = ConnectAttach(0,0,chid_master,0,0);
	//initSTimer();
	//initESTimer();
}

Watchdog::~Watchdog() {

}

void Watchdog::initSTimer() {
	//initialize sendTimer

	SIGEV_PULSE_INIT(&sTimerEvent, coid_master, SIGEV_PULSE_PRIO_INHERIT, CODE_FBM_1, WATCHDOG_SEND_NOTIF);
	timer_create(CLOCK_REALTIME, &sTimerEvent, &sTimerID);
	sTimer.it_value.tv_sec = 0;
	sTimer.it_value.tv_nsec = 750000000;
	sTimer.it_interval.tv_sec = 0;
	sTimer.it_interval.tv_nsec = 150000000;
	timer_settime(sTimerID, 0, &sTimer, NULL);
}

void Watchdog::initESTimer() {
	//initialize EStoppTimer
	SIGEV_PULSE_INIT(&esTimerEvent, coid_master, SIGEV_PULSE_PRIO_INHERIT,
			CODE_FBM_1,
			WATCHDOG_ESTOP);
	if ((timer_create(CLOCK_REALTIME, &esTimerEvent, &esTimerID)) != 0) {
		perror("[Watchdog] timer_create failed");
	}
	esTimer.it_value.tv_sec = 0;
	esTimer.it_value.tv_nsec = 800000000;
	esTimer.it_interval.tv_sec = 0;
	esTimer.it_interval.tv_nsec = 800000000;
	if ((timer_settime(esTimerID, 0, &esTimer, NULL)) != 0) {
		perror("[Watchdog] timer_settime failed");
	}
}
void Watchdog::stopTimer(){
	if ((timer_delete(sTimerID)) != 0) {
		perror("[Watchdog] sTimer_delete failed");
	}
	if ((timer_delete(esTimerID)) != 0) {
		perror("[Watchdog] esTimer_delete failed");
	}
}
void Watchdog::notify() {
//	cout << "[WatchdogMaster] got notified" << endl;
	//delete and reset EStoppTimer
	if ((timer_delete(esTimerID)) != 0) {
		perror("[Watchdog] timer_delete failed");
	}
	initESTimer();
//	cout << "[WatchdogMaster] deleted and reset ESTimer" << endl;
}

