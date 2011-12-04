/*
 * Operations.hxx
 *
 *  Created on: 07/11/2010
 *      Author: adam
 */

#ifndef OPERATIONS_HXX_
#define OPERATIONS_HXX_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Types/Limits.h"

// ---------------------------------------------------------------

namespace Shock {
namespace SafeInteger {

// ---------------------------------------------------------------

template < typename T >
T Operations< T >::add(
	T const & iValue1,
	T const & iValue2,
	Shock::Types::ConversionError & kError
	)
{
	// Taken from
	// https://www.securecoding.cert.org/confluence/display/seccode/INT32-C.+Ensure+that+operations+on+signed+integers+do+not+result+in+overflow

	T iResult( iValue1 );

	if (
		( (iValue1 > 0) && (iValue1 > (Shock::Types::Limits< T >::getMaximum() - iValue2)) ) ||
		( (iValue2 < 0) && (iValue1 < (Shock::Types::Limits< T >::getMinimum() - iValue2)) )
		)
	{
		// overflow condition
		kError.setError(
			Shock::Consts::Types::ConversionError::Overflow
			);
	}
	else
	{
		iResult = iValue1 + iValue2;
	}

	return iResult;
};

// ---------------------------------------------------------------

template < typename T >
T Operations< T >::subtract(
	T const & iValue1,
	T const & iValue2,
	Shock::Types::ConversionError & kError
	)
{
	// Taken from
	// https://www.securecoding.cert.org/confluence/display/seccode/INT32-C.+Ensure+that+operations+on+signed+integers+do+not+result+in+overflow

	T iResult( iValue1 );

	if (
		( (iValue2 > 0) && (iValue1 < (Shock::Types::Limits< T >::getMinimum() + iValue2)) ) ||
		( (iValue2 < 0) && (iValue1 > (Shock::Types::Limits< T >::getMaximum() + iValue2)) )
		)
	{
		// overflow condition
		kError.setError(
			Shock::Consts::Types::ConversionError::Overflow
			);
	}
	else
	{
		iResult = iValue1 - iValue2;
	}

	return iResult;
};

// ---------------------------------------------------------------

template < typename T >
T Operations< T >::multiply(
	T const & iValue1,
	T const & iValue2,
	Shock::Types::ConversionError & kError
	)
{
	// Taken from
	// https://www.securecoding.cert.org/confluence/display/seccode/INT32-C.+Ensure+that+operations+on+signed+integers+do+not+result+in+overflow

	T iResult( iValue1 );
	bool bValid( true );

	if ( iValue1 > 0 )
	{
		// si1 is positive
		if ( iValue2 > 0 )
		{
			// si1 and si2 are positive
			if ( iValue1 > (Shock::Types::Limits< T >::getMaximum() / iValue2) )
			{
				// overflow condition
				kError.setError(
					Shock::Consts::Types::ConversionError::Overflow
					);
				bValid = false;
			}
		}
		else
		{
			//si1 positive, si2 non-positive
			if (iValue2 < (Shock::Types::Limits< T >::getMinimum() / iValue1))
			{
				// overflow condition
				kError.setError(
					Shock::Consts::Types::ConversionError::Overflow
					);
				bValid = false;
			}
		}
	}
	else
	{
		// si1 is non-positive
		if ( iValue2 > 0 )
		{
			// si1 is non-positive, si2 is positive
			if ( iValue1 < (Shock::Types::Limits< T >::getMinimum() / iValue2) )
			{
				// overflow condition
				kError.setError(
					Shock::Consts::Types::ConversionError::Overflow
					);
				bValid = false;
			}
		}
		else
		{
			// si1 and si2 are non-positive
			if (
				(iValue1 != 0) &&
				(iValue2 < (Shock::Types::Limits< T >::getMaximum() / iValue1))
				)
			{
				// overflow condition
				kError.setError(
					Shock::Consts::Types::ConversionError::Overflow
					);
				bValid = false;
			}
		}
	}

	if ( true == bValid )
	{
		iResult = iValue1 * iValue2;
	}

	return iResult;
};

// ---------------------------------------------------------------

template < typename T >
T Operations< T >::divide(
	T const & iValue,
	T const & iDivisor,
	Shock::Types::ConversionError & kError
	)
{
	// Taken from
	// https://www.securecoding.cert.org/confluence/display/seccode/INT32-C.+Ensure+that+operations+on+signed+integers+do+not+result+in+overflow
	T iResult( iValue );

	if ( 0 == Shock::Types::Limits< T >::getMinimum() )
	{
		// don't need to perform this function for unsigned
		iResult = iValue / iDivisor;
	}
	else if (
		(0 == iDivisor) ||
		(
			(Shock::Types::Limits< T >::getMinimum() == iValue) &&
			(-1 == iDivisor)
			)
		)
	{
		// overflow condition
		kError.setError(
			Shock::Consts::Types::ConversionError::Overflow
			);
	}
	else
	{
		iResult = iValue / iDivisor;
	}

	return iResult;
};

// ---------------------------------------------------------------

template < typename T >
T Operations< T >::modulo(
	T const & iValue,
	size_t const & iDivisor,
	Shock::Types::ConversionError & kError
	)
{
	// Taken from
	// https://www.securecoding.cert.org/confluence/display/seccode/INT32-C.+Ensure+that+operations+on+signed+integers+do+not+result+in+overflow
	T iResult( iValue );

	if ( 0 == iDivisor )
	{
		// overflow condition
		kError.setError(
			Shock::Consts::Types::ConversionError::Overflow
			);
	}
	else
	{
		if (
			(iDivisor < 0) &&
			(Shock::Types::Limits< T >::getMinimum() != iDivisor)
			)
	  {
		  iResult = (iValue % -iDivisor);
	  }
	  else
	  {
		  iResult = (iValue % iDivisor);
	  }
	}

	return iResult;
};

// ---------------------------------------------------------------

template < typename T >
T Operations< T >::negative(
	T const & iValue,
	Shock::Types::ConversionError & kError
	)
{
	// Taken from
	// https://www.securecoding.cert.org/confluence/display/seccode/INT32-C.+Ensure+that+operations+on+signed+integers+do+not+result+in+overflow
	T iResult( iValue );

	if ( Shock::Types::Limits< T >::getMinimum() == iValue )
	{
		// overflow condition
		kError.setError(
			Shock::Consts::Types::ConversionError::Overflow
			);
	}
	else
	{
		iResult = -iValue;
	}

	return iResult;
};

// ---------------------------------------------------------------

template < typename T >
T Operations< T >::leftShift(
	T const & iValue,
	size_t const & iNumBits,
	Shock::Types::ConversionError & kError
	)
{
	// Taken from
	// https://www.securecoding.cert.org/confluence/display/seccode/INT32-C.+Ensure+that+operations+on+signed+integers+do+not+result+in+overflow
	T iResult( iValue );

	if (
		(iValue < 0) ||
		(iNumBits < 0) ||
		(iNumBits >= (sizeof( T ) * Shock::Consts::Types::Byte::NumBits)) ||
		(iValue > (Shock::Types::Limits< T >::getMaximum() >> iNumBits))
		)
	{
		// overflow condition
		kError.setError(
			Shock::Consts::Types::ConversionError::Overflow
			);
	}
	else
	{
		iResult = iValue << iNumBits;
	}

	return iResult;
};

// ---------------------------------------------------------------

template < typename T >
T Operations< T >::increment(
	T const & iValue,
	Shock::Types::ConversionError & kError
	)
{
	return add( iValue, 1, kError );
};

// ---------------------------------------------------------------

template < typename T >
T Operations< T >::decrement(
	T const & iValue,
	Shock::Types::ConversionError & kError
	)
{
	return subtract( iValue, 1, kError );
};

// ---------------------------------------------------------------

}; // namespace SafeInteger
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* OPERATIONS_HXX_ */
