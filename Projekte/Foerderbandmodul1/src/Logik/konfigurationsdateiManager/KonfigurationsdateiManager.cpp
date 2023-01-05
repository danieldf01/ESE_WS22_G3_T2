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
		this->set_value_of(Konfi_Codes::HOEHE_HOEHES_WS_MM, 25);
		this->set_value_of(Konfi_Codes::HOEHE_FLACHES_WS_MM, 21);
		this->set_value_of(Konfi_Codes::TIEFE_LOCH_MM, 16);
		this->set_value_of(Konfi_Codes::HYSTERESE_LOCH_MM, 8);
		this->set_value_of(Konfi_Codes::TIEFE_LOCH_KLEIN_MM, 3);
		this->set_value_of(Konfi_Codes::TOLERANZ_MM, 1);
		this->set_value_of(Konfi_Codes::T_RUTSCHE_VOLL, 1000);
		this->set_value_of(Konfi_Codes::TOLERANZ_MESSZEITEN, 50);
		this->set_value_of(Konfi_Codes::FBM1_WS_EINLEGEN_ZEIT, 3000);
		this->set_value_of(Konfi_Codes::ADC_BAND_LEVEL_1, 3651);
		this->set_value_of(Konfi_Codes::ADC_BAND_LEVEL_2, 3651);
		this->set_value_of(Konfi_Codes::ADC_WS_HOCH_LEVEL_1, 2277);
		this->set_value_of(Konfi_Codes::ADC_WS_HOCH_LEVEL_2, 2277);

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
			    lkonf.push_back(std::tuple<std::string,int>(name,std::stoi(value)));
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
		file <<std::get<0>(*it)<< "=" <<std::get<1>(*it)<<std::endl;
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

