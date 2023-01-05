/*
 * FehlerQuittiert.h
 *
 *  Created on: 12.12.2022
 *      Author: acy003
 */

#include "../LogikMain.h"
#include "BaseState.h"
#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_FEHLERQUITTIERT_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_FEHLERQUITTIERT_H_

class FehlerQuittiert : public BaseState{
public:
	void handlePulse(int,int) override;
	void pulseFBM1(int) override;
	void pulseFBM2(int) override;
	void pulseZeit1(int) override;
	void pulseZeit2(int) override;
	void updateAuswertung() override;
	void eStop(int) override;
	void keinFehler();
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_FEHLERQUITTIERT_H_ */
