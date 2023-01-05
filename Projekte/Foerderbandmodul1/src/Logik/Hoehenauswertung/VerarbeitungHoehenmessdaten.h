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


class VerarbeitungHoehenmessdaten {
public:
	VerarbeitungHoehenmessdaten(int anlage, WsListen *wsListen,int hoehe_hoehes_ws_adc, int hoehe_laufband_adc);
	virtual ~VerarbeitungHoehenmessdaten();
	void receivingADCValueFromHAL();
	QnetHandler qnetHandler;
	name_attach_t *attach;
private:
	WsListen *wsListen;
	int anlagen_nr;
	void erkenneWS(double messung_mm);
	double adc_value_to_mm(int dig);
	int slidingwindow(const int messung);
	void clear_HS_daten();

	int hoechster_adc_wert;//kalibrirung
	int keinster_adc_wert;//kalibrirung
	double hoehe_hoehes_ws_mm;
	double hoehe_flaches_ws_mm;
	int hoehe_hoehes_ws_adc;
	int hoehe_laufband_adc;

	double tiefe_loch_mm;
	double hysterese_mm;
	double toleranz_mm;
	double tiefe_loch_klein_mm;

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
