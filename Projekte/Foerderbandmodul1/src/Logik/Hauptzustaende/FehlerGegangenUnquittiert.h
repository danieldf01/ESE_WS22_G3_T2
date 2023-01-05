/*
 * FehlerGegangenUnquittiert.h
 *
 *  Created on: 12.12.2022
 *      Author: acy003
 */


#include "BaseState.h"
#include "../LogikMain.h"

#ifndef LOGIK_HAUPTZUSTAENDE_FEHLERGEGANGENUNQUITTIERT_H_
#define LOGIK_HAUPTZUSTAENDE_FEHLERGEGANGENUNQUITTIERT_H_

class FehlerGegangenUnquittiert : public BaseState{
public:
	void handlePulse(int,int) override;
	void pulseFBM1(int) override;
	void pulseFBM2(int) override;
	void pulseZeit1(int) override;
	void pulseZeit2(int) override;
	void updateAuswertung() override;
	void eStop(int) override;
};

#endif /* LOGIK_HAUPTZUSTAENDE_FEHLERGEGANGENUNQUITTIERT_H_ */
