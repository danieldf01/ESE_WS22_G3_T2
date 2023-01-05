/*
 * WarteSepBisLSEnde.h
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_SEPBISLSENDE_WARTESEPBISLSE1_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_SEPBISLSENDE_WARTESEPBISLSE1_H_

#include "BaseStateSepBisLSE1.h"
#include "FehlerWSZuVielSepBisLSE1.h"
#include "WeicheGeoeffnetSepBisLSE1.h"
#include "WsAufWegZuLSEndeSepBisLSE1.h"

class WarteSepBisLSE1 : public BaseStateSepBisLSE1{
public:
	void entry() override;
	void exit() override;

	//normales Verhalten
	void LsEAn() override;
	void WsPassieren() override;
	void WeicheSchliessen() override;
	void FBM2bereit() override;
	void WsWurdeUebergeben() override;

	//Fehlerverhalten
	void quittiert() override;
	void keinFehler() override;
	void fehlerVerschwunden() override;

	//E-Stop
	void eStop() override;
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_SEPBISLSENDE_WARTESEPBISLSE1_H_ */
