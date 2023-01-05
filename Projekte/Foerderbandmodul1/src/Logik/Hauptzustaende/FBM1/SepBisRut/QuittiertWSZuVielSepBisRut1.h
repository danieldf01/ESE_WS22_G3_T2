/*
 * QuittiertWSZuVielSepBisRut1.h
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_SEPBISRUT_QUITTIERTWSZUVIELSEPBISRUT1_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_SEPBISRUT_QUITTIERTWSZUVIELSEPBISRUT1_H_

#include "BaseStateSepBisRut1.h"
#include "WarteSepBisRut1.h"

class QuittiertWSZuVielSepBisRut1 : public BaseStateSepBisRut1{
public:
	void entry() override;
	void exit() override;

	//normales Verhalten
	void LsRutAn() override;
	void WsAussortieren() override;
	void AuswerferEinfahren() override;

	//Fehlerverhalten
	void quittiert() override;
	void keinFehler() override;
	void Fverschwunden() override;

	//E-Stop
	void eStop() override;
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_SEPBISRUT_QUITTIERTWSZUVIELSEPBISRUT1_H_ */
