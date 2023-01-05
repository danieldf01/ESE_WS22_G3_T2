/*
 * EStop1.h
 *
 *  Created on: Dec 8, 2022
 *      Author: bardi
 */
#include "../LogikMain.h"
#include "BaseState.h"
#ifndef LOGIK_ESTOP1_H_
#define LOGIK_ESTOP1_H_

class EStop : public BaseState {
public:
	void handlePulse(int,int) override;
	void pulseFBM1(int) override;
	void pulseFBM2(int) override;
	void pulseZeit1(int) override;
	void pulseZeit2(int) override;
	void updateAuswertung() override;
	void eStop(int) override;
};

#endif /* LOGIK_ESTOP1_H_ */
