/*
 * WSInLSA2.h
 *
 *  Created on: 22.12.2022
 *      Author: tobias
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANG_WSINLSA2_H_
#define LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANG_WSINLSA2_H_

#include "BaseStateLSA2.h"
#include "WarteAufFBM2.h"
#include "WarteFBM2Frei.h"

class WSInLSA2 : public BaseStateLSA2 {
public:
	void entry() override;
	void exit() override;

	//normales Verhalten
	void lsAnfangAn() override;
	void fbm1Bereit() override;
	void fbm2Bereit() override;
	void fbm1WsLosgeschickt() override;
	void fbm1WsUebergeben() override;
	void lsAnfangAus() override;

	//Fehlerverhalten
	void fehlerVerschwunden() override;
	void quittiert() override;
	void keinFehler() override;

	//E-Stop
	void eStop() override;
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM2_LSANFANG_WSINLSA2_H_ */
