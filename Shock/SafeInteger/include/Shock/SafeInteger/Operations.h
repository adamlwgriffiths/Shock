/*
 * Operations
 *
 *  Created on: 07/11/2010
 *      Author: adam
 */

#ifndef OPERATIONS_H_
#define OPERATIONS_H_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Types/Conversion.h"

// ---------------------------------------------------------------

namespace Shock {
namespace SafeInteger {

// ---------------------------------------------------------------

template < typename T >
class Operations
{
	private:
		Operations() {};
		~Operations() {};

	public:
		static T 		add(
			T const & iValue1,
			T const & iValue2,
			Shock::Types::ConversionError & kError
			);

		static T		subtract(
			T const & iValue1,
			T const & iValue2,
			Shock::Types::ConversionError & kError
			);

		static T		multiply(
			T const & iValue1,
			T const & iValue2,
			Shock::Types::ConversionError & kError
			);

		static T		divide(
			T const & iValue,
			T const & iDivisor,
			Shock::Types::ConversionError & kError
			);

		static T		modulo(
			T const & iValue,
			size_t const & iDivisor,
			Shock::Types::ConversionError & kError
			);

		static T		negative(
			T const & iValue,
			Shock::Types::ConversionError & kError
			);

		static T		leftShift(
			T const & iValue,
			size_t const & iNumBits,
			Shock::Types::ConversionError & kError
			);

		static T		increment(
			T const & iValue,
			Shock::Types::ConversionError & kError
			);

		static T		decrement(
			T const & iValue,
			Shock::Types::ConversionError & kError
			);
};

// ---------------------------------------------------------------

}; // namespace SafeInteger
}; // namespace Shock

// ---------------------------------------------------------------

// include our template implementation
#include "Shock/SafeInteger/Operations.hxx"

// ---------------------------------------------------------------

#endif /* OPERATIONS_H_ */
