/*
 * KonfigurationsdateiManager.h
 *
 *  Created on: 13.12.2022
 *      Author: m
 */

#ifndef SRC_KONFIGURATIONSDATEIMANAGER_KONFIGURATIONSDATEIMANAGER_H_
#define SRC_KONFIGURATIONSDATEIMANAGER_KONFIGURATIONSDATEIMANAGER_H_

#include <iostream>
#include <fstream>
#include <string>
#include "Konfi_enums.h"
#include "Konfi_string_table.h"
#include <tuple>
#include <list>

const std::string einleitung = "#Hallo lieber Benutzer!?\n#dies ist ihre liebebliche sowie Benutzerfreundliche \n#aber hauptsächlich störrische Konfigurationsdatei.\n#\n#Um die Werkstück Reihenfolge festzulegen\n#konfigurieren sie die untenstehenden Variablen WS_Reihung_1-3 \n#hier bei können sie nach dem = den Typ festlegen.\n#Beispiel: „WS_Reihung_Nr_1=1“\n#bedeutet das als erstes en Flaches Werkstück zur Reihung gehört.\n#Die Zeitwerte sind in ms zu verstehen\n#Von allem anderen lassen sie einfach die Finger solange sie das nicht vorhandende Benutzerhandbuch nicht gelesen haben.\n#####################################\n# Flaches Werkstück=0\n# Hohes Werkstück mit Bohrung ohne Metalleinsatz=2\n# Hohes Werkstück mit Bohrung mit Metalleinsatz=3\n# Hohes Werksück ohne Bohrung=1\n#####################################\n";



class KonfigurationsdateiManager {
public:
	KonfigurationsdateiManager(std::string filename);
	virtual ~KonfigurationsdateiManager();
	void printList();
	int dateieinlesen();
	void speicherInKonfigurationsdatei();
	int get_value_of(Konfi_Codes name);
	int set_value_of(Konfi_Codes name,int value);
private:
	void erstelleKonfigurationsdatei();
	std::list<std::tuple<std::string, int>> lkonf;
	std::string filename;
};


#endif /* SRC_KONFIGURATIONSDATEIMANAGER_KONFIGURATIONSDATEIMANAGER_H_ */
