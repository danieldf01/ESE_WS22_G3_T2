/*
 * VerarbeitungHoehenmessdaten.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Marek
 */

#include "VerarbeitungHoehenmessdaten.h"

VerarbeitungHoehenmessdaten::VerarbeitungHoehenmessdaten(int anlage) {
	qnetHandler = QnetHandler();
	if (anlage == 1) {
		attach = qnetHandler.openServer(AUSWERTUNG_1);
	} else {
		attach = qnetHandler.openServer(AUSWERTUNG_2);
	}
	this->anlage = anlage;

	receivingRunning = true;
	stopAn = true;
	logikID = 0;
	ws_erkannt = false;
	WS_Typ = UNBEKANNT;
	loch_tief_cnt = 0;
	loch_Hysterese = false;
	hoechste_messung = 0;
	HoheMitteWs = 0;
	mittlereHohe = 0;

	//debug diese Werte werden zur Kalibrirung benötigt
	hoechster_adc_wert = 0; //wert des Laufbands
	keinster_adc_wert = INT_MAX; //höchstes gemessendes WS

}

VerarbeitungHoehenmessdaten::~VerarbeitungHoehenmessdaten() {
	// TODO Auto-generated destructor stub
}

//als Thread starten
void VerarbeitungHoehenmessdaten::receivingADCValueFromHAL(WsListen *wsListen) { //TODO Unterscheidung Wert von Anlage 1 oder 2
	this->wsListen = wsListen;
	bool fehlergeworfen = false;

	_pulse msg;
	while (receivingRunning) {
		int recvid = MsgReceive(attach->chid, &msg, sizeof(_pulse), nullptr);

		if (recvid < 0) {
			perror("MsgReceivePulse failed!");
			exit(EXIT_FAILURE);
		}

		if (msg.type == _IO_CONNECT) {// some sync msg was received
			std::cout << AUSWERTUNG_1 << " received _IO_CONNECT via sync. message" << std::endl;
			MsgReply(recvid, EOK, NULL, 0);
			logikID = qnetHandler.connectServer(LOGIK);
		}

		if (recvid == 0) {	//pulse received.

			if (msg.value.sival_int == MOTOR_STOP_AN) {
				stopAn = true;
			}
			if (msg.value.sival_int == MOTOR_STOP_AUS) {
				stopAn = false;
				fehlergeworfen = false;//TODO das hier muss dassieren bei quitiert
			}
			if (msg.value.sival_int == HS_LEEREN) {
				this->clear_HS_daten();
			}

			//ADC interrupt value.
			if (msg.code == PULSE_ADC_SAMLING_WINDOW_DONE) {
				int messung = msg.value.sival_int;
				messung = this->slidingwindow(messung);
				if (hoechster_adc_wert < messung) {hoechster_adc_wert = messung;} //braucchen wir später in Kalibrirungsmodus
				//cout << "HS hoechst:" << hoechster_adc_wert << endl;
				if (keinster_adc_wert > messung) {keinster_adc_wert = messung;} //braucchen wir später in Kalibrirungsmodus
				//cout << "HS kleinster:" << keinster_adc_wert << endl;
				double messung_mm = this->adc_value_to_mm(messung);
				//cout << "MESSUNGINMM: "<<messung_mm << endl;

				if(!stopAn){
					this->erkenneWS(messung_mm);
				}else{ //TODO Multiplikator HW:3 SIM:10
					if (messung_mm >= this->adc_value_to_mm(hoehe_laufband) + (toleranz_mm*10) && !fehlergeworfen) {
						fehlergeworfen = true;
						MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL + anlage, HS_AKTIV);
						cout << "HS_AKTIV STOERFAKTOR" << endl;
						fflush(stdout);
					}
				}

			}
		}
	}
}

void VerarbeitungHoehenmessdaten::erkenneWS(double messung_mm){
	/*=======================Erkenne Werkstück=======================*/
	if (ws_erkannt == false && (messung_mm >= (hoehe_flaches_ws_mm - toleranz_mm))) {
		ws_erkannt = true;
		WS_Typ = FLACH;
		MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL + anlage, HS_AKTIV);
		cout << "HS_AKTIV geschickt" << endl;
	}

	//WS in Höhenmessung
	if (ws_erkannt) {

		mlist.push_back(messung_mm); //messung in list einfügen
		if (hoechste_messung < messung_mm) {
			hoechste_messung = messung_mm;
		}

		//hohes WS erkennen
		if (messung_mm >= hoehe_hoehes_ws_mm - toleranz_mm && WS_Typ == FLACH) {
			WS_Typ = HOCH_OB;
		}
		//WS_mit_Loch oder WS_verläst_HS
		else if (loch_Hysterese == false && (WS_Typ == HOCH_OB && messung_mm <= hoechste_messung - tiefe_loch_mm + toleranz_mm)) {
			loch_Hysterese = true;

		} else if (loch_Hysterese) {
			if (messung_mm > hoechste_messung - tiefe_loch_mm + toleranz_mm + hysterese_mm) {
				loch_tief_cnt++;
				loch_Hysterese = false;
			}
		}

		//Werkstück hat HS durchquert
		if (messung_mm <= 0 + toleranz_mm) {
//			cout << "Werkstück hat HS durchquert Timestamp:" << wsListen->getWsHoehensensor1()->getTimestamp() << endl;
			//berechne Arithmetisches mittel
			for (auto it = mlist.begin(); it != mlist.end(); ++it) {
				mittlereHohe += *it;
			}
			mittlereHohe = mittlereHohe / mlist.size();

			//Debug liste ausgeben
			//for (auto it = mlist.begin(); it != mlist.end(); ++it){cout << *it << endl;}//liste ausgeben debug

			//finde mittler messung in liste
			std::list<double>::iterator it = mlist.begin();
			advance(it, mlist.size() / 2);
			HoheMitteWs = *it;

			//WS typ auswerten
			if (loch_tief_cnt == 1) {
				WS_Typ = HOCH_MB;
			} else if (loch_tief_cnt > 1) {
				WS_Typ = UNBEKANNT;
			}
			if (WS_Typ == HOCH_OB && hoechste_messung - tiefe_loch_klein_mm > HoheMitteWs) {
				WS_Typ = UNBEKANNT;
			}
			/*=======================Erkenne Werkstück ENDE=======================*/

			//Ausgabe
			printf("TYP: %d mittlere Höhe: %.2f Höhe Mitte des Werkstücks: %.2f Loch: %d hoechste_messung: %.2f neueMessung %.2f MAX_ADC: %d MIN_ADC: %d\n",
					WS_Typ, mittlereHohe, HoheMitteWs,loch_tief_cnt, hoechste_messung, messung_mm, hoechster_adc_wert, keinster_adc_wert);
			if (WS_Typ == FLACH) {
				printf("FLACH\n");
				if (anlage == 1) {
					wsListen->ws_Hoehensensor_1->setWsTyp(FLACH);
				} else {
					wsListen->ws_Hoehensensor_2->setWsTyp(FLACH);
				}
			}
			if (WS_Typ == HOCH_OB) {
				printf("HOCH_OHNE_BOHRUNG\n");
				if (anlage == 1) {
					wsListen->ws_Hoehensensor_1->setWsTyp(HOCH_OB);
				} else {
					wsListen->ws_Hoehensensor_2->setWsTyp(HOCH_OB);
				}
			}
			if (WS_Typ == HOCH_MB) {
				printf("HOCH_MIT_BOHRUNG\n");
				if (anlage == 1) {
					wsListen->ws_Hoehensensor_1->setWsTyp(HOCH_MB);
				} else {
					wsListen->ws_Hoehensensor_2->setWsTyp(HOCH_MB);
				}
			}
			if (WS_Typ == UNBEKANNT) {
				printf("UNBEKANNT\n");
				if (anlage == 1) {
					wsListen->ws_Hoehensensor_1->setWsTyp(UNBEKANNT);
				} else {
					wsListen->ws_Hoehensensor_2->setWsTyp(UNBEKANNT);
				}
			}
//			cout << "BEFORE WS_TYP SEND " << wsListen->getWsHoehensensor1()->getTimestamp() << endl;
			MsgSendPulse(logikID, SIGEV_PULSE_PRIO_INHERIT, _PULSE_CODE_MINAVAIL + anlage, WS_TYP);
			fflush(stdout);

			//aufräumen für nächstes werkstück
			this->clear_HS_daten();

		}
	}
}

void VerarbeitungHoehenmessdaten::clear_HS_daten(){
	ws_erkannt = false;
	WS_Typ = UNBEKANNT;
	loch_tief_cnt = 0;
	hoechste_messung = 0;
	loch_Hysterese = false;
	HoheMitteWs = 0;
	mittlereHohe = 0;
	mlist.clear();
}


double VerarbeitungHoehenmessdaten::adc_value_to_mm(int dig) {

	double entfernung = 0;
	int i = 0;

	if (dig < hoehe_laufband) {

		double v_delta = dig - lookup_ADC_Value[i];
		double steigung = ((lookup_mm[i + 1] - lookup_mm[i]) / (lookup_ADC_Value[i + 1] - lookup_ADC_Value[i]));
		entfernung = lookup_mm[i] + v_delta * steigung;
		return entfernung;
	}

	return entfernung;
}

int VerarbeitungHoehenmessdaten::slidingwindow(const int messung) {
	static int messung_array[SLIDING_WINDOW_SIZE];
	static int index = 0;
	static bool init = true;
	int ret = -1;

	//inti Array first time
	if (init) {
		for (int var = 0; var < SLIDING_WINDOW_SIZE; var++) {
			messung_array[var] = hoehe_laufband;
		}
		init = false;
	}

	//sliding window
	messung_array[index] = messung;
	for (int var = 0; var < SLIDING_WINDOW_SIZE; var++) {
		ret += messung_array[var];
	}

	//Ringbuffer verhalten
	index++;
	if (index >= SLIDING_WINDOW_SIZE) {
		index = 0;
	}
	return ret / SLIDING_WINDOW_SIZE;
}
