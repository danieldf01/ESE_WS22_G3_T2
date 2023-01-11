/*
 * Hauptzustand.h
 *
 *  Created on: 04.12.2022
 *      Author: User
 */

#ifndef SRC_HAUPTZUSTAND_H_
#define SRC_HAUPTZUSTAND_H_

#include <iostream>
#include "../LogikMain.h"
#include "BaseState.h"
#include "Betriebszustand.h"


class Ruhezustand : public BaseState {
public:
	void handlePulse(int, int) override;
	void pulseFBM1(int) override;
	void pulseFBM2(int) override;
	void pulseZeit1(int) override;
	void pulseZeit2(int) override;
	void updateAuswertung() override;
	void eStop(int) override;
	void initTimer();
	void destroyTimer();
};

#endif /* SRC_HAUPTZUSTAND_H_ */
