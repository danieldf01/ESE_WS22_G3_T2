/*
 * KonfigurationsdateiManager.cpp
 *
 *  Created on: 13.12.2022
 *      Author: m
 */

#include "KonfigurationsdateiManager.h"


KonfigurationsdateiManager::KonfigurationsdateiManager(std::string filename) {
	this->filename=filename;
	int r =this->dateieinlesen();
	if(r<0){
		std::cout << "erstelle Datei: " << filename << std::endl;
		this->erstelleKonfigurationsdatei();
		this->dateieinlesen();
		this->set_value_of(Konfi_Codes::ADC_WS_HOCH_LEVEL_1, 2339);
		this->set_value_of(Konfi_Codes::ADC_BAND_LEVEL_1,3646);
		this->set_value_of(Konfi_Codes::ADC_WS_HOCH_LEVEL_2, 2339);
		this->set_value_of(Konfi_Codes::ADC_BAND_LEVEL_2,3646);
		this->set_value_of(Konfi_Codes::T_RUTSCHE_VOLL, 1000);
		this->set_value_of(Konfi_Codes::FBM1_WS_EINLEGEN_ZEIT, 2000);
		this->set_value_of(Konfi_Codes::FBM1_LAENGSTE_ZEIT_BIS_HS, 3000);
		this->set_value_of(Konfi_Codes::FBM1_LAENGSTE_ZEIT_BIS_SEP, 1500);
		this->set_value_of(Konfi_Codes::FBM1_LAENGSTE_ZEIT_BIS_LS_RUT, 2400);
		this->set_value_of(Konfi_Codes::FBM1_LAENGSTE_ZEIT_BIS_LS_ENDE, 3500);
		this->set_value_of(Konfi_Codes::FBM1_LAENGSTE_ZEIT_WS_UEBERGEBEN, 400);
		this->set_value_of(Konfi_Codes::FBM1_ZEIT_WS_PASSIERT_WEICHE, 1000);
		this->set_value_of(Konfi_Codes::FBM2_LAENGSTE_ZEIT_BIS_HS, 3000);
		this->set_value_of(Konfi_Codes::FBM2_LAENGSTE_ZEIT_BIS_SEP, 1500);
		this->set_value_of(Konfi_Codes::FBM2_LAENGSTE_ZEIT_BIS_LS_RUT, 2400);
		this->set_value_of(Konfi_Codes::FBM2_LAENGSTE_ZEIT_BIS_LS_ENDE, 3500);
		this->set_value_of(Konfi_Codes::FBM2_ZEIT_WS_PASSIERT_WEICHE, 1000);
		this->set_value_of(Konfi_Codes::EINLEGE_ZEIT_AUSWERFER, 500);
		this->set_value_of(Konfi_Codes::EINLEGE_ZEIT_WEICHE, 1550);
		this->set_value_of(Konfi_Codes::WS_Reihung_Nr_1,1);
		this->set_value_of(Konfi_Codes::WS_Reihung_Nr_2,2);
		this->set_value_of(Konfi_Codes::WS_Reihung_Nr_3,3);
		this->MQTTaddress="tcp://192.168.140.1:1883";
		this->MQTTclientID="FESTO_Client_Pub";
		this->MQTTtopic="/Festo/128";
		this->speicherInKonfigurationsdatei();
	}

}

KonfigurationsdateiManager::~KonfigurationsdateiManager() {
	// TODO Auto-generated destructor stub
}


void KonfigurationsdateiManager::erstelleKonfigurationsdatei(){
	std::ofstream file;
	std::string line;
	file.open(filename);
	file << einleitung;

	for(int i = 0; i < (int)Konfi_Codes::MAX_ENUM; i++){
		file << MsgCodeStrings[i] << "=0" << std::endl;
	}
	file.close();
}

int KonfigurationsdateiManager::dateieinlesen(){
	std::ifstream file;
	std::string line;
	file.open(filename);
	std::string delimiter = "=";

	if(file.is_open()){
		while(std::getline(file, line)){
			if(line[0] == '#') continue;
			//std::cout <<"[FULL LINE]" << line << std::endl;

			size_t pos = 0;
			std::string name;
			std::string value;
			while ((pos = line.find(delimiter)) != std::string::npos) {
			    name = line.substr(0, pos);
			    line.erase(0, pos + delimiter.length());
			    value = line;

				if(name == MsgCodeStrings[Konfi_Codes::MQTTaddress] ){//etwas uneleganter fix für Mqtt da strings
//					std::cout << "MQTTaddress: "<<value<<std::endl;
					MQTTaddress = value;
					lkonf.push_back(std::tuple<std::string,int>(name,0));
				}
				else if(name == MsgCodeStrings[Konfi_Codes::MQTTclientID] ){
//					std::cout << "MQTTclientID: "<<value<<std::endl;
					MQTTclientID = value;
					lkonf.push_back(std::tuple<std::string,int>(name,0));
				}
				else if(name == MsgCodeStrings[Konfi_Codes::MQTTtopic] ){
//					std::cout << "MQTTtopic: "<<value <<std::endl;
					MQTTtopic = value;
					lkonf.push_back(std::tuple<std::string,int>(name,0));
				}
				else{
					lkonf.push_back(std::tuple<std::string,int>(name,std::stoi(value)));
				}
			}
		}

	}else{
		std::cout << "Fehler beim Öffnen der Datei: " << filename << std::endl;
		file.close();
		return -1;
	}
	file.close();
	return 0;
}


void KonfigurationsdateiManager::speicherInKonfigurationsdatei(){
	std::ofstream file;
	std::string line;
	file.open(filename);
	file << einleitung;


	for (auto it = lkonf.begin(); it != lkonf.end(); ++it){
		if(std::get<0>(*it) == MsgCodeStrings[Konfi_Codes::MQTTaddress] ){//etwas uneleganter fix für Mqtt da strings
//			std::cout << "MQTTaddress"<<std::endl;
			file <<std::get<0>(*it)<< "=" << MQTTaddress<<std::endl;
		}
		else if(std::get<0>(*it) == MsgCodeStrings[Konfi_Codes::MQTTclientID] ){
//			std::cout << "MQTTclientID"<<std::endl;
			file <<std::get<0>(*it)<< "=" << MQTTclientID<<std::endl;
		}
		else if(std::get<0>(*it) == MsgCodeStrings[Konfi_Codes::MQTTtopic] ){
//			std::cout << "MQTTtopic"<<std::endl;
			file <<std::get<0>(*it)<< "=" << MQTTtopic<<std::endl;
		}
		else{
			file <<std::get<0>(*it)<< "=" <<std::get<1>(*it)<<std::endl;
		}
	}
	file.close();
}



int KonfigurationsdateiManager::get_value_of(Konfi_Codes name){
	for (auto it = lkonf.begin(); it != lkonf.end(); ++it){
		if( std::get<0>(*it)== MsgCodeStrings[name]){
			return std::get<1>(*it);
		}
	}
	return -1;
}



int KonfigurationsdateiManager::set_value_of(Konfi_Codes name, int value){
	for (auto it = lkonf.begin(); it != lkonf.end(); ++it){
		if( std::get<0>(*it)== MsgCodeStrings[name]){
			std::get<1>(*it) = value;
			return 0;
		}
	}
	return -1;
}



void KonfigurationsdateiManager::printList(){
	std::cout << "########################################" <<std::endl;
	printf("listSize=%d\n",lkonf.size());
	for (auto it = lkonf.begin(); it != lkonf.end(); ++it){
		std::cout <<std::get<0>(*it)<< "=" <<std::get<1>(*it)<<std::endl;
	}
	std::cout << "########################################" <<std::endl;
}

