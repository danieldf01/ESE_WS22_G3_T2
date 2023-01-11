/*
 * Watchdog.cpp
 *
 *  Created on: 25.11.2022
 *      Author: Daniel Drefs Fernandes
 */

#include "Watchdog.h"

Watchdog::Watchdog(int chid_s) {
	this->chid_slave = chid_s;
}

Watchdog::~Watchdog() {
	// TODO Auto-generated destructor stub
}

void Watchdog::init() {
	coid_slave = ConnectAttach(0, 0, chid_slave, 0, 0);
	//initSTimer();
	//initESTimer();
}

void Watchdog::initSTimer() {
	//initialize sendTimer
	SIGEV_PULSE_INIT(&sTimerEvent, coid_slave, SIGEV_PULSE_PRIO_INHERIT,
			CODE_FBM_2, WATCHDOG_SEND_NOTIF);
	if ((timer_create(CLOCK_REALTIME, &sTimerEvent, &sTimerID)) == -1) {
		perror("[Watchdog] timer_create for sendTimer failed");
	}
	sTimer.it_value.tv_sec = 0;
	sTimer.it_value.tv_nsec = 750000000;
	sTimer.it_interval.tv_sec = 0;
	sTimer.it_interval.tv_nsec = 750000000;
	if ((timer_settime(sTimerID, 0, &sTimer, NULL)) == -1) {
		perror("[Watchdog] timer_settime for sendTimer failed");
	}
}

void Watchdog::initESTimer() {
	//initialize EStoppTimer
	SIGEV_PULSE_INIT(&esTimerEvent, coid_slave, SIGEV_PULSE_PRIO_INHERIT,
			CODE_FBM_2, WATCHDOG_ESTOP);
	if ((timer_create(CLOCK_REALTIME, &esTimerEvent, &esTimerID)) == -1) {
		perror("[Watchdog] timer_create for EStopTimer failed");
	}
	esTimer.it_value.tv_sec = 0;
	esTimer.it_value.tv_nsec = 800000000;
	esTimer.it_interval.tv_sec = 0;
	esTimer.it_interval.tv_nsec = 800000000;
	if ((timer_settime(esTimerID, 0, &esTimer, NULL)) == -1) {
		perror("[Watchdog] timer_settime for EStopTimer failed");
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
//	std::cout << "[WatchdogSlave] got notified" << std::endl;
	//delete and reset EStoppTimer
	if ((timer_delete(esTimerID)) != 0) {
		perror("[Watchdog] timer_delete failed");
	}
	initESTimer();
//	std::cout << "[WatchdogSlave] deleted and reset ESTimer" << std::endl;
}

