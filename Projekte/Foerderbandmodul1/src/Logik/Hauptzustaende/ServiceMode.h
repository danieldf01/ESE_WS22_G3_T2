/*
 * ServiceMode.h
 *
 *  Created on: Jan 6, 2023
 *      Author: bardi
 */

#ifndef LOGIK_HAUPTZUSTAENDE_SERVICEMODE_H_
#define LOGIK_HAUPTZUSTAENDE_SERVICEMODE_H_

#include "../LogikMain.h"
#include "BaseState.h"

class ServiceMode : public BaseState{
public:
	int durchlauf;

	unsigned int zeitLSAaus;
	unsigned int zeitHSaus;
	unsigned int zeitSepAn;
	unsigned int zeitSepAus;
	unsigned int zeitEndeAus;

	unsigned int zeitLSAbisHS;
	unsigned int zeitHSbisSep;
	unsigned int zeitSepbisRutsche;
	unsigned int zeitSepbisEnde;
	unsigned int zeitEndebisLSA2;

	unsigned int zeitSepbisEnde2;


	void handlePulse(int, int) override;
	void pulseFBM1(int) override;
	void pulseFBM2(int) override;
	void pulseZeit1(int) override;
	void pulseZeit2(int) override;
	void updateAuswertung() override;
	void eStop(int) override;
	void durchlassen(int);
	void aussortieren(int);
};

#endif /* LOGIK_HAUPTZUSTAENDE_SERVICEMODE_H_ */
