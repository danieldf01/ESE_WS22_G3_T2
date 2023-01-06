/*
 * FehlerWSZuVielSepBisLSEnde.h
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM2_SEPBISLSENDE_FEHLERWSZUVIELSEPBISLSE2_H_
#define LOGIK_HAUPTZUSTAENDE_FBM2_SEPBISLSENDE_FEHLERWSZUVIELSEPBISLSE2_H_

#include "BaseStateSepBisLSE2.h"
#include "QuittiertZuVielSepBisLSE2.h"

class FehlerWSZuVielSepBisLSE2 : public BaseStateSepBisLSE2 {
public:
	void entry() override;
	void exit() override;

	//normales Verhalten
	void LsEAn() override;
	void LsEAus() override;
	void WsPassieren() override;
	void WeicheSchliessen() override;

	//Fehlerverhalten
	void quittiert() override;
	void keinFehler() override;
	void fehlerVerschwunden() override;

	//E-Stop
	void eStop() override;
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM2_SEPBISLSENDE_FEHLERWSZUVIELSEPBISLSE2_H_ */