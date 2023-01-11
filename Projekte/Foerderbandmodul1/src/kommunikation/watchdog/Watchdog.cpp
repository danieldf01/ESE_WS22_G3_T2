/*
 * watchdog.cpp
 *
 *  Created on: 11.01.2023
 *      Author: m
 */

#include "Watchdog.h"



Watchdog::Watchdog(OutputDispatcher &dispatcher) {
	this->zeit = 0;
	this->outputDispatcher = &dispatcher;
	this->qnetHandler = new QnetHandler();
	std::cout << "createWatchdog1" << std::endl;

}

Watchdog::~Watchdog() {
	// TODO Auto-generated destructor stub
}


void Watchdog::threadWatchdog() {

	attach = qnetHandler->openServer("Watchdog1");


	_pulse msg;
	bool receivingRunning = true;
	std::cout << "Watchdog pulse tread receive running" << std::endl;
	while (receivingRunning) {
		int recvid = MsgReceivePulse(attach->chid, &msg, sizeof(_pulse),nullptr);
		std::cout << "Watchdog pulse received puls:"<< msg.value.sival_int << std::endl;
		if (recvid < 0) {
			perror("MsgReceivePulse failed!");
			exit(EXIT_FAILURE);
		}

		if (recvid == 0) {	//pulse received.


			if(msg.value.sival_int == WATCHDOG_INIT){
				Watchdog::startTimerPeriodisch(TIMER_INTERVAL, attach->chid);
				coid_kommunikation=qnetHandler->connectServer(SERVER_KOM_MASTER);
				std::cout << "createWatchdog INIT" << std::endl;
			}

			if(msg.value.sival_int == WATCHDOG_NOTIF/*puls des anderen watchdog*/){
				zeit = 0;
			}

			if(msg.value.sival_int == 1/*Timer puls alle 10 ms*/){
				zeit += 1;
				std::cout << "Watchdog Zeit: "<< zeit << std::endl;
				if(zeit > 20){
					outputDispatcher->dispatchOutput(WATCHDOG_ESTOP, 0);
				}
				else if(zeit == 5){
					/*sende puls an andern watchdog*/
					std::cout << "Watchdog1 WATCHDOG_NOTIF -> 2: "<< zeit << std::endl;
					MsgSendPulse(coid_kommunikation, SIGEV_PULSE_PRIO_INHERIT , CODE_FBM_1, WATCHDOG_NOTIF);
				}
			}
		}
	}
	std::cout << "watchdog left the loop"<< std::endl;

}

void Watchdog::startTimerPeriodisch(int intervalNanoSek, int chid) {
	timer_t timerid;
	struct sigevent event;
	struct itimerspec timer;
	int coid;

	coid = ConnectAttach(0, 0, chid, 0, 0);

	SIGEV_PULSE_INIT(&event, coid, SIGEV_PULSE_PRIO_INHERIT,
			_PULSE_CODE_MINAVAIL + 5, 1);

	// Hier wird ein Timer erstellt mit CLOCK_REALTIME und einem sigevent
	timer_create(CLOCK_REALTIME, &event, &timerid);	//Fehlerbehandlung fehlt

	// Setup und Start eines periodischen Timers
	timer.it_value.tv_sec = 0;
	timer.it_value.tv_nsec = intervalNanoSek; // Macht hier eine Runde, anschließend wird das intervall unten verwendet
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_nsec = intervalNanoSek; // Hier wird angegeben, wann der timer wieder neu starten soll fuer periodisch timer

	// Hier wird der timer gestartet
	// Benutzt die timerid von dem erstellten timer oben, flags: abs/rel,
	timer_settime(timerid, 0, &timer, NULL);
}


