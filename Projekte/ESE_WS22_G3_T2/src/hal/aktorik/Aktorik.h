/*
 * Aktorik.h
 *
 *  Created on: 17.10.2022
 *  Author: Tobias Thoelen
 *
 *	Hier sind alle Biblotheken definiert die fuer
 *	die Visualisierung und Benutzung der Aktorik wichtig sind.
 */

#ifndef HAL_AKTORIK_AKTORIK_H_
#define HAL_AKTORIK_AKTORIK_H_

#include <stdint.h>
#include <sys/mman.h>
#include <hw/inout.h>

#include "../../simulation/simulationadapterqnx/simqnxgpioapi.h" //simulation include

#define GPIO_CLEARDATAOUT 0x190
#define GPIO_SETDATAOUT 0x194
#define GPIO_OE_REGISTER 0x134

#endif /* HAL_AKTORIK_AKTORIK_H_ */
