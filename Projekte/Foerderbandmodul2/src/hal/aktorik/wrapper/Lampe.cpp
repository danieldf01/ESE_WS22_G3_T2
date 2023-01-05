/*
 * lampen.cpp
 *
 *  Created on: 16.10.2022
 *  Author: Tobias Thoelen
 */
#include "Lampe.h"




using namespace std;

Lampe::Lampe() {
	gpio_bank_1 = mmap_device_io(0x1000, (uint64_t) 0x4804C000);
	out32((uintptr_t) (gpio_bank_1 + GPIO_OE_REGISTER_AKT), 0x00000000);
}

Lampe::~Lampe() {
}


void Lampe::lampeGruenAn() {
	out32((uintptr_t) (gpio_bank_1 + GPIO_SETDATAOUT_AKT), GRUENE_LAMPE);
}

void Lampe::lampeGruenAus() {
	out32((uintptr_t) (gpio_bank_1 + GPIO_CLEARDATAOUT_AKT), GRUENE_LAMPE);
}

void Lampe::lampeGelbAn() {
	out32((uintptr_t) (gpio_bank_1 + GPIO_SETDATAOUT_AKT), GELBE_LAMPE);
}

void Lampe::lampeGelbAus() {
	out32((uintptr_t) (gpio_bank_1 + GPIO_CLEARDATAOUT_AKT), GELBE_LAMPE);
}

void Lampe::lampeRotAn() {
	out32((uintptr_t) (gpio_bank_1 + GPIO_SETDATAOUT_AKT), ROTE_LAMPE);
}

void Lampe::lampeRotAus() {
	out32((uintptr_t) (gpio_bank_1 + GPIO_CLEARDATAOUT_AKT), ROTE_LAMPE);
}

/**
 * @parameter die Farbe Gruen, Gelb oder Rot.
 */
void Lampe::lampeAn(Farbe farbe) {
	switch(farbe){
			case 0:
				lampeGruenAn();
				break;
			case 1:
				lampeGelbAn();
				break;
			case 2:
				lampeRotAn();
				break;
		}
}

/**
 * @parameter die Farbe Gruen, Gelb oder Rot.
 */
void Lampe::lampeAus(Farbe farbe) {
	switch(farbe){
			case 0:
				lampeGruenAus();
				break;
			case 1:
				lampeGelbAus();
				break;
			case 2:
				lampeRotAus();
				break;
		}
}
//void Lampe::lampeAn(int farben) {
//	switch (farben) {
//		case 1:
//			lampeGruenAn();
//			break;
//		case 10:
//			lampeGelbAn();
//			break;
//		case 100:
//			lampeRotAn();
//			break;
//		case 11:
//			lampeGruenAn();
//			lampeGelbAn();
//			break;
//		case 101:
//			lampeGruenAn();
//			lampeRotAn();
//			break;
//		case 110:
//			lampeRotAn();
//			lampeGelbAn();
//			break;
//		case 111:
//			lampeGruenAn();
//			lampeGelbAn();
//			lampeRotAn();
//			break;
//
//	}
//}
//
///**
// * @parameter die Farbe Gruen, Gelb oder Rot.
// */
//void Lampe::lampeAus(int farben) {
//	switch(farben){
//		case 1:
//			lampeGruenAus();
//			break;
//		case 10:
//			lampeGelbAus();
//			break;
//		case 100:
//			lampeRotAus();
//			break;
//		case 11:
//			lampeGruenAus();
//			lampeGelbAus();
//			break;
//		case 101:
//			lampeGruenAus();
//			lampeRotAus();
//			break;
//		case 110:
//			lampeRotAus();
//			lampeGelbAus();
//			break;
//		case 111:
//			lampeGruenAus();
//			lampeGelbAus();
//			lampeRotAus();
//			break;
//		}
//}
