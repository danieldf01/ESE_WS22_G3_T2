/*
 * WsListen.h
 *
 *  Created on: Dec 11, 2022
 *      Author: bardi
 */

#ifndef LOGIK_WSLISTEN_H_
#define LOGIK_WSLISTEN_H_

#include <list>
#include "Werkstueck.h"
#include <mutex>

using namespace std;

class WsListen {
public:
	//Mutexe für die Listen
	mutex lSAnfang_bis_HS_m;
	mutex hs_bis_seperator_m;
	mutex passieren_m;
	mutex aussortieren_m;

	mutex ws_Hoehensensor_1_m;

	//Werkstueck auf FBM1
	list<Werkstueck> ws_list_LSAnfang_bis_HS;
	list<Werkstueck> ws_list_HS_bis_Seperator;
	list<Werkstueck> ws_list_passieren;
	list<Werkstueck> ws_list_aussortieren;
	list<int> sortierReihenfolge;
	Werkstueck *ws_LSAnfang = nullptr;
	Werkstueck *ws_Hoehensensor_1=nullptr;

	//Werkstueck auf dem FBM2
	Werkstueck *ws_Hoehensensor_2=nullptr;
	Werkstueck *ws_ls_anfang_2=nullptr;
	Werkstueck *ws_ls_anfang_bis_hs_2=nullptr;
	Werkstueck *ws_hs_bis_seperator_2=nullptr;
	Werkstueck *ws_passieren_2=nullptr;
	Werkstueck *ws_aussortieren_2=nullptr;
	WsListen();
	virtual ~WsListen();
	void emptyAll();

	Werkstueck *getWsHoehensensor1(){
		ws_Hoehensensor_1_m.lock();
		Werkstueck *tempWS = ws_Hoehensensor_1;
		ws_Hoehensensor_1_m.unlock();
		return tempWS;
	}

	void setWsHoehensensor1(Werkstueck *tempWS){
		ws_Hoehensensor_1_m.lock();
		ws_Hoehensensor_1 = tempWS;
		ws_Hoehensensor_1_m.unlock();
	}
};

#endif /* LOGIK_WSLISTEN_H_ */
