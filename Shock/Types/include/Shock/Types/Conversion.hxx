/*
 * Conversion.hxx
 *
 *  Created on: 08/11/2010
 *      Author: adam
 */

#ifndef CONVERSION_HXX_
#define CONVERSION_HXX_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Types/Limits.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Types {

// ---------------------------------------------------------------

template < typename InType, typename OutType >
OutType Conversion< InType, OutType >::convert( InType iIn, ConversionError & kError )
{
	OutType iResult( 0 );

	// check if the input value is negative
	// if so, check if the output type is signed
	if (
		(iIn < 0) &&
		(Shock::Types::Limits< OutType >::getMinimum() == 0)
		)
	{
		// the out type is signed
		// we can't do the conversion
		kError.setError(
			Shock::Consts::Types::ConversionError::Overflow
			);
	}
	else
	{
		// the type is not negative
		// or our output type is signed and our input is negative
		// check that the type is without our output maximum and minimum
		if (
			(Shock::Types::Limits< OutType >::getMaximum() < iIn) ||
			(Shock::Types::Limits< OutType >::getMinimum() > iIn)
			)
		{
			// the value is outside our range
			kError.setError(
				Shock::Consts::Types::ConversionError::Overflow
				);
		}
		else
		{
			// value is within our range
			// perform the conversion
			iResult = static_cast< OutType >( iIn );
		}
	}

	return iResult;
}

// ---------------------------------------------------------------

}; // namespace Time
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* CONVERSION_HXX_ */
