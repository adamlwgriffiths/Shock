/*
 * Limits.h
 *
 *  Created on: 20/06/2010
 *      Author: Adam Griffiths
 */

#ifndef LIMITS_H_
#define LIMITS_H_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Types/Types.h"

// Standard Includes
#include <limits.h>

// ---------------------------------------------------------------

namespace Shock {
namespace Consts {
namespace Types {

// ---------------------------------------------------------------

namespace Byte {
Shock::Types::uint8_t const NumBits	= CHAR_BIT;
};

// ---------------------------------------------------------------
// Standard Types

namespace Char {
char const Max						= CHAR_MAX;
char const Min						= CHAR_MIN;
};

// ---------------------------------------------------------------

namespace Uchar {
unsigned char const Max				= UCHAR_MAX;
unsigned char const Min				= 0;
};

// ---------------------------------------------------------------

namespace Schar {
signed char const Max				= SCHAR_MAX;
signed char const Min				= SCHAR_MIN;
};

// ---------------------------------------------------------------

namespace Short {
short int const Max					= SHRT_MAX;
short int const Min					= SHRT_MIN;
};

// ---------------------------------------------------------------

namespace Ushort {
unsigned short int const Max		= USHRT_MAX;
unsigned short int const Min		= 0;
};

// ---------------------------------------------------------------

namespace Int {
int const Max						= INT_MAX;
int const Min						= INT_MIN;
};

// ---------------------------------------------------------------

namespace Uint {
unsigned int const Max				= UINT_MAX;
unsigned int const Min				= 0;
};

// ---------------------------------------------------------------

namespace Long {
long int const Max					= LONG_MAX;
long int const Min					= LONG_MIN;
};

// ---------------------------------------------------------------

namespace Ulong {
unsigned long int const Max			= ULONG_MAX;
unsigned long int const Min			= 0;
};

// ---------------------------------------------------------------
// Fixed width types

namespace Int8 {
Shock::Types::int8_t const Max		= 0x7F;
Shock::Types::int8_t const Min		= 0x80;
};

// ---------------------------------------------------------------

namespace Int16 {
Shock::Types::int16_t const Max		= 0x7FFF;
Shock::Types::int16_t const Min		= 0x8000;
};

// ---------------------------------------------------------------

namespace Int32 {
Shock::Types::int32_t const Max		= 0x7FFFFF;
Shock::Types::int32_t const Min		= 0x800000;
};

// ---------------------------------------------------------------

namespace Int64 {
Shock::Types::int64_t const Max		= 0x7FFFFFFFFFFF;
Shock::Types::int64_t const Min		= 0x800000000000;
};

// ---------------------------------------------------------------

namespace Uint8 {
Shock::Types::uint8_t const Max		= 0xFF;
Shock::Types::uint8_t const Min		= 0x00;
};

// ---------------------------------------------------------------

namespace Uint16 {
Shock::Types::uint16_t const Max		= 0xFFFF;
Shock::Types::uint16_t const Min		= 0x0000;
};

// ---------------------------------------------------------------

namespace Uint32 {
Shock::Types::uint32_t const Max		= 0xFFFFFF;
Shock::Types::uint32_t const Min		= 0x000000;
};

// ---------------------------------------------------------------

namespace Uint64 {
Shock::Types::uint64_t const Max		= 0xFFFFFFFFFFFF;
Shock::Types::uint64_t const Min		= 0x000000000000;
};

// ---------------------------------------------------------------

namespace Size {
Shock::Types::size_t const Max		= -1;
Shock::Types::size_t const Min		= 0;
/*
#if defined(SHOCK_PLATFORM_BITS_32)
	Shock::Types::size_t const Max		= 0xFFFFFF;
	Shock::Types::size_t const Min		= 0x000000;
#elif defined(SHOCK_PLATFORM_BITS_64)
	Shock::Types::size_t const Max		= 0xFFFFFFFFFFFF;
	Shock::Types::size_t const Min		= 0x000000000000;
#else
#	error SHOCK_PLATFORM_BITS_32 or SHOCK_PLATFORM_BITS_64 not defined
#endif
*/
};

// ---------------------------------------------------------------

namespace PtrDiff {
Shock::Types::ptrdiff_t const Max			= (Shock::Consts::Types::Size::Max >> 1);
Shock::Types::ptrdiff_t const Min			= Shock::Consts::Types::Size::Max;
/*
#if defined(SHOCK_PLATFORM_BITS_32)
	Shock::Types::ptrdiff_t const Max		= 0x7FFFFF;
	Shock::Types::ptrdiff_t const Min		= 0x800000;
#elif defined(SHOCK_PLATFORM_BITS_64)
	Shock::Types::ptrdiff_t const Max		= 0x7FFFFFFFFFFF;
	Shock::Types::ptrdiff_t const Min		= 0x800000000000;
#else
#	error SHOCK_PLATFORM_BITS_32 or SHOCK_PLATFORM_BITS_64 not defined
#endif
*/
};
// ---------------------------------------------------------------

}; // namespace Types
}; // namespace Consts
}; // namespace Shock

// ---------------------------------------------------------------

namespace Shock {
namespace Types {

// ---------------------------------------------------------------

template < typename T >
class Limits
{
	private:
		Limits() {};
		~Limits() {};

	public:
		static inline T			getMaximum();
		static inline T			getMinimum();
};

// ---------------------------------------------------------------

}; // namespace Types
}; // namespace Shock

// ---------------------------------------------------------------

// include our template implementation
#include "Shock/Types/Limits.hxx"

// ---------------------------------------------------------------

#endif /* LIMITS_H_ */
