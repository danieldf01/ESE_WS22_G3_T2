/*
 * myenums.h
 *
 *  Created on: 03.03.2022
 *      Author: Lehmann
 */

#ifndef SRC_KONFI_ENUMS_H_
#define SRC_KONFI_ENUMS_H_


#define ESTRING(x) x,

typedef enum {
	#include "Konfi_estring_defs.h"
} Konfi_Codes;
#undef ESTRING



#endif /* SRC_KONFI_ENUMS_H_ */
