/*
 * WartenLSAbisHS.h
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_LSANFANGBISHS_WARTENLSABISHS1_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_LSANFANGBISHS_WARTENLSABISHS1_H_

#include "BaseStateLSAbisHS1.h"
#include "FehlerWsZuVielLSAbisHS1.h"
#include "WsAufWegZumHsLSAbisHS1.h"

class WartenLSAbisHS1: public BaseStateLSAbisHS1 {
public:
	void entry() override;
	void exit() override;

	//normales Verhalten
	void WSinLSAbisHS() override;
	void HSaktiv() override;	//auch fuer WS zu frueh beim HS (WS vorgeschoben),
								//Werkstueck verschwunden

	//Fehlerverhalten
	void quittiert() override;
	void keinFehler() override;
	//Werkstueck verschwunden
	void Fverschwunden() override;
	//E-Stop
	void eStop() override;
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_LSANFANGBISHS_WARTENLSABISHS1_H_ */
