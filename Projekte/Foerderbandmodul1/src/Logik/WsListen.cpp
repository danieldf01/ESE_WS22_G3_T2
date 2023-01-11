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
	ws_list_LSAnfang_bis_HS.clear();
	ws_list_HS_bis_Seperator.clear();
	ws_list_aussortieren.clear();
	ws_list_passieren.clear();
	ws_list_sep_bis_lsende.clear();
	ws_Hoehensensor_1=nullptr;
	ws_Hoehensensor_2=nullptr;
	ws_ls_anfang_2=nullptr;
	ws_ls_anfang_bis_hs_2=nullptr;
	ws_hs_bis_seperator_2=nullptr;
	ws_passieren_2=nullptr;
	ws_aussortieren_2=nullptr;
}
