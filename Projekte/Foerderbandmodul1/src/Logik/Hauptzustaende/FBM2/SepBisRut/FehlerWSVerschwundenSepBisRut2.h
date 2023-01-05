/*
 * FehlerWSVerschwundenSepBisRut2.h
 *
 *  Created on: 21.12.2022
 *      Author: acx514
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM2_SEPBISRUT_FEHLERWSVERSCHWUNDENSEPBISRUT2_H_
#define LOGIK_HAUPTZUSTAENDE_FBM2_SEPBISRUT_FEHLERWSVERSCHWUNDENSEPBISRUT2_H_

#include "BaseStateSepBisRut2.h"
#include "QuittiertWSVerschwundenSepBisRut2.h"

class FehlerWSVerschwundenSepBisRut2 : public BaseStateSepBisRut2{
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

#endif /* LOGIK_HAUPTZUSTAENDE_FBM2_SEPBISRUT_FEHLERWSVERSCHWUNDENSEPBISRUT2_H_ */
