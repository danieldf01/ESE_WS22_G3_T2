/*
 * BaseStatePassieren.h
 *
 *  Created on: 07.01.2023
 *      Author: mario
 */

#ifndef LOGIK_HAUPTZUSTAENDE_FBM1_PASSIEREN_BASESTATEPASSIEREN_H_
#define LOGIK_HAUPTZUSTAENDE_FBM1_PASSIEREN_BASESTATEPASSIEREN_H_

#include "ActionsPassieren.h"
#include "../../../konfigurationsdateiManager/KonfigurationsdateiManager.h"

class BaseStatePassieren {
protected:
	ActionsPassieren *actions;
	WsListen *wsListen;
	KonfigurationsdateiManager *konfig;
public:
	virtual ~BaseStatePassieren() {};

	void setActions(ActionsPassieren *actions){this->actions = actions;};
	void setWsListen(WsListen *wsListen) {this->wsListen = wsListen;};
	void setKonfig(KonfigurationsdateiManager *konfig) {this->konfig = konfig;};

	virtual void entry() = 0;
	virtual void exit() = 0;

	//normales Verhalten
	virtual void WsPassieren() = 0;
	virtual void WeicheSchliessen() = 0;

	//E-Stop
	virtual void eStop() = 0;
};

#endif /* LOGIK_HAUPTZUSTAENDE_FBM1_PASSIEREN_BASESTATEPASSIEREN_H_ */
