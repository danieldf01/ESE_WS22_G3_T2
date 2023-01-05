/*
 * WartenWsNichtAussortierbar.h
 *
 *  Created on: 21.12.2022
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FEHLERWSNICHTAUSSORTIERBAR_WARTENWSNICHTAUSSORTIERBAR_H_
#define LOGIK_HAUPTZUSTAENDE_FEHLERWSNICHTAUSSORTIERBAR_WARTENWSNICHTAUSSORTIERBAR_H_

#include "BaseStateWsNichtAussortierbar.h"
#include "FehlerRutsche2Voll.h"
#include "FehlerRutsche1Und2Voll.h"

class WartenWsNichtAussortierbar : public BaseStateWsNichtAussortierbar {
public:
	void entry() override;
	void exit() override;

	void WsNichtAussortierbar() override;
	void LsRutscheAus1() override;
	void LsRutscheAus2() override;

	void eStop() override;
};

#endif /* LOGIK_HAUPTZUSTAENDE_FEHLERWSNICHTAUSSORTIERBAR_WARTENWSNICHTAUSSORTIERBAR_H_ */
