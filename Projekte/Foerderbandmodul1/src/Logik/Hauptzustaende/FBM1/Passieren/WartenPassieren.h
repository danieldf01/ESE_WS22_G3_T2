/*
 * WartenPassieren.h
 *
 *  Created on: 07.01.2023
 *      Author: Daniel Drefs Fernandes
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_PASSIEREN_WARTENPASSIEREN_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_PASSIEREN_WARTENPASSIEREN_H_

#include "BaseStatePassieren.h"
#include "WeicheGeoeffnetPassieren.h"

class WartenPassieren : public BaseStatePassieren{
public:
	void entry() override;
	void exit() override;

	//normales Verhalten
	void WsPassieren() override;
	void WeicheSchliessen() override;

	//E-Stop
	void eStop() override;
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_PASSIEREN_WARTENPASSIEREN_H_ */
