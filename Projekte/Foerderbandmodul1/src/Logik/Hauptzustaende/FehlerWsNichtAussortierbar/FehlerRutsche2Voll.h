/*
 * FehlerRutsche2Voll.h
 *
 *  Created on: 21.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FEHLERWSNICHTAUSSORTIERBAR_FEHLERRUTSCHE2VOLL_H_
#define LOGIK_HAUPTZUSTAENDE_FEHLERWSNICHTAUSSORTIERBAR_FEHLERRUTSCHE2VOLL_H_

#include "BaseStateWsNichtAussortierbar.h"
#include "WartenWsNichtAussortierbar.h"

class FehlerRutsche2Voll : public BaseStateWsNichtAussortierbar {
public:
	void entry() override;
	void exit() override;

	void WsNichtAussortierbar() override;
	void LsRutscheAus1() override;
	void LsRutscheAus2() override;

	void eStop() override;
};

#endif /* LOGIK_HAUPTZUSTAENDE_FEHLERWSNICHTAUSSORTIERBAR_FEHLERRUTSCHE2VOLL_H_ */
