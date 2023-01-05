/*
 * WartenHSBisSep2.h
 *
 *  Created on: 17.12.2022
 *      Author: tobias
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM2_HSBISSEP_WARTENHSBISSEP2_H_
#define LOGIK_HAUPTZUSTAENDE_FBM2_HSBISSEP_WARTENHSBISSEP2_H_

#include "BaseStateHSBisSep2.h"
#include "FehlerWSZuVielHSBisSep2.h"
#include "WSAufWegZumSep2.h"

class WartenHSBisSep2: public BaseStateHSBisSep2 {
public:
	void entry() override;
	void exit() override;

	//normales Verhalten
	void WSinHSbisSep() override;
	void MetSenAn() override;			//auch fuer Fehler WS zu viel
	void LSSepAn() override;			//auch fuer Fehler WS zu viel und WS zu frueh
	void aussortieren1() override;
	void aussortieren2() override;
	void aussortieren3() override;

	//Fehlerverhalten
	void quittiert() override;
	void keinFehler() override;
	void fehlerCntDown() override;
	//Werkstueck verschwunden
	void fehlerVerschwunden() override;
	//E-Stop
	void eStop() override;
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM2_HSBISSEP_WARTENHSBISSEP2_H_ */
