/*
 * Endian.h
 *
 *  Created on: 20/06/2010
 *      Author: adam
 */

#ifndef ENDIAN_H_
#define ENDIAN_H_

// ---------------------------------------------------------------
// Shock Includes

#if defined ( SHOCK_ENDIAN_BIG )
#	include "Shock/Endian/BigEndian.h"
#elif defined ( SHOCK_ENDIAN_LITTLE )
#	include "Shock/Endian/LittleEndian.h"
#else
#	error SHOCK_ENDIAN_BIG or SHOCK_ENDIAN_LITTLE not defined
#endif

// ---------------------------------------------------------------

#endif /* ENDIAN_H_ */
