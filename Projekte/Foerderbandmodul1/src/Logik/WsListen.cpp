/*
 * WsListen.cpp
 *
 *  Created on: Dec 11, 2022
 *      Author: bardi
 */

#include "WsListen.h"

WsListen::WsListen() {

}

WsListen::~WsListen() {

}

void WsListen::emptyAll(){
	ws_LSAnfang.~Werkstueck();
	ws_list_LSAnfang_bis_HS.clear();
	ws_list_HS_bis_Seperator.clear();
	ws_list_aussortieren.clear();
	ws_list_passieren.clear();
	ws_list_sep_bis_lsende.clear();
	ws_Hoehensensor_1.~Werkstueck();
	ws_Hoehensensor_2.~Werkstueck();
	ws_ls_anfang_2.~Werkstueck();
	ws_ls_anfang_bis_hs_2.~Werkstueck();
	ws_hs_bis_seperator_2.~Werkstueck();
	ws_passieren_2.~Werkstueck();
	ws_aussortieren_2.~Werkstueck();
//	delete &ws_LSAnfang;
//	delete &ws_Hoehensensor_1;
//	delete &ws_Hoehensensor_2;
//	delete &ws_ls_anfang_2;
//	delete &ws_ls_anfang_bis_hs_2;
//	delete &ws_hs_bis_seperator_2;
//	delete &ws_passieren_2;
//	delete &ws_aussortieren_2;
}
