/*
 * VerarbeitungHoehenmessdaten.h
 *
 *  Created on: 30.11.2022
 *      Author: Marek
 */




#ifndef SRC_VERARBEITUNGHOEHENMESSDATEN_H_
#define SRC_VERARBEITUNGHOEHENMESSDATEN_H_

#include <stdio.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <iostream>
#include <list>
#include <time.h>
#include "../../dispatcher/QnetHandler.h"
#include "../WsListen.h"
#include "../Defines.h"

/* My pulse codes */
#define PULSE_STOP_THREAD _PULSE_CODE_MINAVAIL + 1
#define PULSE_ADC_SAMLING_DONE _PULSE_CODE_MINAVAIL + 2
#define PULSE_ADC_SAMLING_WINDOW_DONE _PULSE_CODE_MINAVAIL + 3

#define SLIDING_WINDOW_SIZE 1 //HW 15 SIM 1

//#define hoehe_hoehes_ws 2277+
//#define hoehe_laufband 3651+

//const double hoehe_hoehes_ws_mm = 25.0;+
//const double hoehe_flaches_ws_mm = 21.0;+

//const double tiefe_loch_mm = 16.0;//muss größer toleranz_mm+
//const double hysterese_mm = 8.0;+
//const double toleranz_mm = 1.0;
//
//const double tiefe_loch_klein_mm = 3.0;+
//




class VerarbeitungHoehenmessdaten {
public:
	double hoehe_hoehes_ws_mm;
	double hoehe_flaches_ws_mm;
	double tiefe_loch_mm;

	int hoehe_hoehes_ws;
	int hoehe_laufband;
	double hysterese_mm;
	double toleranz_mm;
	double tiefe_loch_klein_mm;
	//const double lookup_mm[2] = 		{0,	hoehe_hoehes_ws_mm};
	//const double lookup_ADC_Value[2] = {hoehe_laufband, hoehe_hoehes_ws};
	double lookup_mm[2];
	double lookup_ADC_Value[2];

	WsListen *wsListen;
	int anlage;
	VerarbeitungHoehenmessdaten(int);
	virtual ~VerarbeitungHoehenmessdaten();
	QnetHandler qnetHandler;
	name_attach_t *attach;
	void receivingADCValueFromHAL(WsListen *wsListen);

	int hoechster_adc_wert;//kalibrirung
	int keinster_adc_wert;//kalibrirung
private:
	void erkenneWS(double messung_mm);
	double adc_value_to_mm(int dig);
	int slidingwindow(const int messung);
	void clear_HS_daten();
	bool receivingRunning;
	bool stopAn;
	int logikID;
	bool ws_erkannt;
	int WS_Typ;
	int loch_tief_cnt;
	bool loch_Hysterese;
	double hoechste_messung;
	double HoheMitteWs;
	double mittlereHohe;
	std::list<double> mlist;
};

#endif /* SRC_VERARBEITUNGHOEHENMESSDATEN_H_ */
