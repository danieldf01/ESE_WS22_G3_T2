/*
 * QuittiertZuFruehHSBisSep1.h
 *
 *  Created on: 19.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_HSBISSEP_QUITTIERTZUFRUEHHSBISSEP1_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_HSBISSEP_QUITTIERTZUFRUEHHSBISSEP1_H_

#include "BaseStateHSBisSep1.h"
#include "WSAufWegZumSep1.h"

class QuittiertZuFruehHSBisSep1 : public BaseStateHSBisSep1 {
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
	void aussortieren4() override;

	//Fehlerverhalten
	void quittiert() override;
	void keinFehler() override;
	void fehlerCntDown() override;
	//Werkstueck verschwunden
	void fehlerVerschwunden() override;
	//E-Stop
	void eStop() override;
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_HSBISSEP_QUITTIERTZUFRUEHHSBISSEP1_H_ */
