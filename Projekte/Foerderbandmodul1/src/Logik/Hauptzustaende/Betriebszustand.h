/*
 * Betriebszustand.h
 *
 *  Created on: 07.12.2022
 *      Author: acy003
 */

#ifndef LOGIK_BETRIEBSZUSTAND_H_
#define LOGIK_BETRIEBSZUSTAND_H_

#include "../LogikMain.h"
#include "BaseState.h"

class Betriebszustand : public BaseState {
public:
	void handlePulse(int, int) override;
	void pulseFBM1(int) override;
	void pulseFBM2(int) override;
	void pulseZeit1(int) override;
	void pulseZeit2(int) override;
	void updateAuswertung() override;
	void eStop(int) override;
	void initTimer();
};

#endif /* LOGIK_BETRIEBSZUSTAND_H_ */
