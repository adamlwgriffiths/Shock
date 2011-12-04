/*
 * Memory.h
 *
 *  Created on: 03/10/2010
 *      Author: Adam Griffiths
 */

#ifndef MEMORY_H_
#define MEMORY_H_

// ---------------------------------------------------------------

#define SHOCK_SAFE_DELETE( pPtr )	\
do {															\
	delete pPtr;										\
	pPtr = 0;												\
} while ( 0 )

// ---------------------------------------------------------------

#define SHOCK_SAFE_DELETE_ARRAY( pPtr )	\
do {															\
	delete [] pPtr;									\
	pPtr = 0;												\
} while( 0 )

// ---------------------------------------------------------------

#endif /* MEMORY_H_ */
