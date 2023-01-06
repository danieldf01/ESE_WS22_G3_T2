/*
 * BaseState.h
 *
 *  Created on: 04.12.2022
 *      Author: User
 */


#ifndef BASESTATE_H_
#define BASESTATE_H_
#include <iostream>
#include "../Zeit/Zeitmanager.h"
#include "../konfigurationsdateiManager/KonfigurationsdateiManager.h"
#include "../Hoehenauswertung/VerarbeitungHoehenmessdaten.h"

class BaseState {
public:
	virtual ~BaseState() {};

	Zeitmanager *zeitFBM1;
	Zeitmanager *zeitFBM2;

	WsListen *wsListen;

	KonfigurationsdateiManager *dateiManager = nullptr;

	VerarbeitungHoehenmessdaten *hoehenauswertung1 = nullptr;
	VerarbeitungHoehenmessdaten *hoehenauswertung2 = nullptr;
	bool eStop2;
	bool eStop1;
	bool langGedrueckt;

	int fehlerCount;
	int warnungsCount;
	bool fehlerQuittiert;
	//Qnet connection IDs
	int inputID;
	int kommID;
	int auswertungID1;
	int auswertungID2;
	int fsmWsNichtAussortierbar_ID;
	int fsmLSA1_ID;
	int fsmLSAbisHS1_ID;
	int fsmWsErkennung1_ID;
	int fsmHSbisSep1_ID;
	int fsmSepBisRut1_ID;
	int fsmSepBisLSEnde1_ID;

	// TODO ALLE IDS added
	int fsmLSA2_ID;
	int fsmLSAbisHS2_ID;
	int fsmWsErkennung2_ID;
	int fsmHSbisSep2_ID;
	int fsmSepBisRut2_ID;
	int fsmSepBisLSEnde2_ID;

	int motorID;
	int rutschenID;

	virtual void handlePulse(int code, int value) = 0;
	virtual void pulseFBM1(int value) = 0;
	virtual void pulseFBM2(int value) = 0;
	virtual void pulseZeit1(int value) = 0;
	virtual void pulseZeit2(int value) = 0;
	virtual void updateAuswertung() = 0;
	virtual void eStop(int) = 0;
};

#endif /* BASESTATE_H_ */
