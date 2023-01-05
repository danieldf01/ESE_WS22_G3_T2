/*
 * Laufband.cpp
 *
 *  Created on: 17.10.2022
 *  Author: Tobias Thoelen
 */
#include "Laufband.h"


Laufband::Laufband() {
	gpio_bank_1 = mmap_device_io(0x1000, (uint64_t) 0x4804C000);
	out32((uintptr_t) (gpio_bank_1 + GPIO_OE_REGISTER_AKT), 0x00000000);
}

Laufband::~Laufband() {
}


void Laufband::laufbandRechtsAn() {
	out32((uintptr_t) (gpio_bank_1 + GPIO_SETDATAOUT_AKT), LAUFBANDRECHTS);
}

void Laufband::laufbandRechtsAus() {
	out32((uintptr_t) (gpio_bank_1 + GPIO_CLEARDATAOUT_AKT), LAUFBANDRECHTS);
}

void Laufband::laufbandLinksAn() {
	out32((uintptr_t) (gpio_bank_1 + GPIO_SETDATAOUT_AKT), LAUFBANDLINKS);
}

void Laufband::laufbandLinksAus() {
	out32((uintptr_t) (gpio_bank_1 + GPIO_CLEARDATAOUT_AKT), LAUFBANDLINKS);
}

void Laufband::laufbandLangsamAn() {
	out32((uintptr_t) (gpio_bank_1 + GPIO_SETDATAOUT_AKT), LAUFBANDLANGSAM);
}

void Laufband::laufbandLangsamAus() {
	out32((uintptr_t) (gpio_bank_1 + GPIO_CLEARDATAOUT_AKT), LAUFBANDLANGSAM);
}

void Laufband::laufbandStopAn() {
	out32((uintptr_t) (gpio_bank_1 + GPIO_SETDATAOUT_AKT), LAUFBANDSTOP);
}
void Laufband::laufbandStopAus() {
	out32((uintptr_t) (gpio_bank_1 + GPIO_CLEARDATAOUT_AKT), LAUFBANDSTOP);
}
