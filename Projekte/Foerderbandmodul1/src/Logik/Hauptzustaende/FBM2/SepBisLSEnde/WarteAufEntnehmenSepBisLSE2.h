/*
 * Warteaufentnehmen.h
 *
 *  Created on: 06.01.2023
 *      Author: tobi
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM2_SEPBISLSENDE_WARTEAUFENTNEHMENSEPBISLSE2_H_
#define LOGIK_HAUPTZUSTAENDE_FBM2_SEPBISLSENDE_WARTEAUFENTNEHMENSEPBISLSE2_H_

#include "BaseStateSepBisLSE2.h"

class WarteAufEntnehmenSepBisLSE2 : public BaseStateSepBisLSE2  {
public:
	void entry() override;
	void exit() override;

	//normales Verhalten
	void LsEAn() override;
	void LsEAus() override;
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

#endif /* LOGIK_HAUPTZUSTAENDE_FBM2_SEPBISLSENDE_WARTEAUFENTNEHMENSEPBISLSE2_H_ */
