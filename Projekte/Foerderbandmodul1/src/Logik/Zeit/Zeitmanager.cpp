/*
 * Zeitmanager.cpp
 *
 *  Created on: 09.12.2022
 *      Author: Tobias Thoelen
 */
// TODO Es fehlt timer für mehrere Zeitüberwachung gleichzeitig!
#include "Zeitmanager.h"

using namespace std;

Zeitmanager::Zeitmanager(unsigned int schnell, unsigned int langsam, int chid,
		int pulse_code) {
	this->pulse_code = pulse_code;
	this->chid = chid;
	this->coid = ConnectAttach(0, 0, chid, _NTO_SIDE_CHANNEL, 0);
	this->currentSpeed = 0;
	this->zeit = 0;
	this->schnell = schnell;
	this->langsam = langsam;

}

Zeitmanager::~Zeitmanager() {
	// TODO Auto-generated destructor stub
}

/**
 * Zaehlt die Zeit hoch (globaler Timer)
 */
void Zeitmanager::threadStartZeit() {
	int chidReciveTimer = ChannelCreate(0);
	Zeitmanager::startTimerPeriodisch(TIMER_INTERVAL, chidReciveTimer);

	_pulse msg;
	bool receivingRunning = true;

	while (receivingRunning) {
		int recvid = MsgReceivePulse(chidReciveTimer, &msg, sizeof(_pulse),
				nullptr);

		if (recvid < 0) {
			perror("MsgReceivePulse failed!");
			exit(EXIT_FAILURE);
		}

		if (recvid == 0) {	//pulse received.

			zeit += (currentSpeed * 1); //TODO hier 10ms es ist wichtig das Zeitgeber alle 10ms einen pulse sendet
			/*Übergprüfer ob ein Timer in der liste abgelaufen*/
			for (auto it = lmessungen.begin(); it != lmessungen.end(); ++it) {
				if (std::get<0>(*it) <= zeit) {

					MsgSendPulse(coid, SIGEV_PULSE_PRIO_INHERIT, pulse_code,
							std::get<0>(std::get<1>(*it)));
					//printf("Messung abgeschlossen:%d Payload:%d\n",std::get<0>(*it),std::get<1>(*it));
					lmessungen.erase(it);

				}
			}

		}
	}
	cout << "Zeitmanager left the loop"<< endl;

}

void Zeitmanager::startTimerPeriodisch(int intervalNanoSek, int chid) {
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

unsigned int Zeitmanager::getTime() {
	return zeit;
}

void Zeitmanager::setTimerSpeedLangsam() {
	currentSpeed = langsam;
}

void Zeitmanager::setTimerSpeedSchnell() {
	currentSpeed = schnell;
}

void Zeitmanager::setTimerSpeedStop() {
	currentSpeed = 0;
}

void Zeitmanager::startMessung(unsigned int millisek, int pulse_payload, int wsID) {
	tuple<int, int> tupel(pulse_payload, wsID);
	lmessungen.push_back(tuple<unsigned int, tuple<int, int>>(millisek, tupel));

}
void Zeitmanager::clearLists(){
	if(!lmessungen.empty()){
	lmessungen.clear();
	}

}

void Zeitmanager::deleteTimer(int wsID){
	for (auto it = lmessungen.begin(); it != lmessungen.end(); ++it) {
		if (std::get<1>(std::get<1>(*it)) == wsID) {
			lmessungen.erase(it);
//			std::cout << "deleted timer, wsID (parameter): " << wsID << ", ID in Liste: " << std::get<1>(std::get<1>(*it)) << endl;
		}
	}
}
