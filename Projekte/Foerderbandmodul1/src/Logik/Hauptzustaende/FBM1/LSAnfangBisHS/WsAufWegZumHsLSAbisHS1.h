/*
 * WsAufWegZumHsLSAbisHS.h
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_LSANFANGBISHS_WSAUFWEGZUMHSLSABISHS1_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_LSANFANGBISHS_WSAUFWEGZUMHSLSABISHS1_H_

#include "BaseStateLSAbisHS1.h"
#include "FehlerWsVerschwundenLSAbisHS1.h"
#include "FehlerWsZuFruehLSAbisHS1.h"
#include "WartenLSAbisHS1.h"


class WsAufWegZumHsLSAbisHS1 : public BaseStateLSAbisHS1{
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

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_LSANFANGBISHS_WSAUFWEGZUMHSLSABISHS1_H_ */
