/*
 * WarteMessungWsErkennung1.h
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_WSERKENNUNG_WARTEMESSUNGWSERKENNUNG1_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_WSERKENNUNG_WARTEMESSUNGWSERKENNUNG1_H_

#include "BaseStateWsErkennung1.h"
#include "FehlerHoehenmessungWsErkennung1.h"

class WarteMessungWsErkennung1 : public BaseStateWsErkennung1 {
public:

	//TODO Temp
	int timestamp = 0;
	// TODO Temp

	void entry() override;
	void exit() override;

	//normales Verhalten
	void WSinHS() override;
	void WsTyp() override;		//auch fuer Fehler Hoehenmessung (WS zu schnell oder verschwunden)

	//Fehlerverhalten
	void quittiert() override;
	void keinFehler() override;
	//Werkstueck zu schnell oder verschwunden
	void fehlerHoehenmessung() override;
	//E-Stop
	void eStop() override;
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_WSERKENNUNG_WARTEMESSUNGWSERKENNUNG1_H_ */
