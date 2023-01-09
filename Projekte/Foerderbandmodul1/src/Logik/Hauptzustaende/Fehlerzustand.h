/*
 * Fehlerzustand.h
 *
 *  Created on: 12.12.2022
 *      Author: acy003
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FEHLERZUSTAND_H_
#define LOGIK_HAUPTZUSTAENDE_FEHLERZUSTAND_H_

#include "../LogikMain.h"
#include "BaseState.h"

class Fehlerzustand :public BaseState{
public:
	void handlePulse(int, int) override;
	void pulseFBM1(int) override;
	void pulseFBM2(int) override;
	void pulseZeit1(int) override;
	void pulseZeit2(int) override;
	void updateAuswertung() override;
	void eStop(int) override;
	void quittiert();
	void initTimer1();;
	void initTimer2();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FEHLERZUSTAND_H_ */
