/*
 * mystringtable.h
 *
 *  Created on: 03.03.2022
 *      Author: Lehmann
 */

#ifndef SRC_KONFI_STRING_TABLE_H_
#define SRC_KONFI_STRING_TABLE_H_

#define ESTRING(x) #x,

static const char* MsgCodeStrings[] = {
	#include "Konfi_estring_defs.h"
};
#undef ESTRING

#endif /* SRC_KONFI_STRING_TABLE_H_ */
