/*
 * WsAufWegZumHsLSAbisHS.h
 *
 *  Created on: 14.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANGBISHS_WSAUFWEGZUMHSLSABISHS2_H_
#define LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANGBISHS_WSAUFWEGZUMHSLSABISHS2_H_

#include "BaseStateLSAbisHS2.h"
#include "FehlerWsVerschwundenLSAbisHS2.h"
#include "FehlerWsZuFruehLSAbisHS2.h"
#include "WartenLSAbisHS2.h"


class WsAufWegZumHsLSAbisHS2 : public BaseStateLSAbisHS2{
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

#endif /* LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANGBISHS_WSAUFWEGZUMHSLSABISHS2_H_ */
