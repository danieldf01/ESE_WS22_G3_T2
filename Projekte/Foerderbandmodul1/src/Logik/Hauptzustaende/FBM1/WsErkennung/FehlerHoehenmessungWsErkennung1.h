/*
 * FehlerHoehenmessungWsErkennung1.h
 *
 *  Created on: 15.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_WSERKENNUNG_FEHLERHOEHENMESSUNGWSERKENNUNG1_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_WSERKENNUNG_FEHLERHOEHENMESSUNGWSERKENNUNG1_H_

#include "BaseStateWsErkennung1.h"
#include "QuittiertWsErkennung1.h"

class FehlerHoehenmessungWsErkennung1 : public BaseStateWsErkennung1 {
public:
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

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_WSERKENNUNG_FEHLERHOEHENMESSUNGWSERKENNUNG1_H_ */
