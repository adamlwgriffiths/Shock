/*
 * Bits.h
 *
 *  Created on: 20/06/2010
 *      Author: Adam Griffiths
 */

#ifndef BITS_H_
#define BITS_H_

// ---------------------------------------------------------------
// Standard Includes
#include <string>

// ---------------------------------------------------------------

namespace Shock {
namespace Consts {
namespace Platform {

// ---------------------------------------------------------------

namespace Bits
{
	enum _t
	{
			Bits32		= 32,
			Bits64		= 64,
	};
};

// ---------------------------------------------------------------

namespace Bits32 {

// ---------------------------------------------------------------

std::string const Description(
	"32-Bit"
	);

// ---------------------------------------------------------------

}; // namespace Bits32

// ---------------------------------------------------------------

namespace Bits64 {

// ---------------------------------------------------------------

std::string const Description(
	"64-Bit"
	);

// ---------------------------------------------------------------

}; // namespace Bits64

// ---------------------------------------------------------------

}; // namespace Platform
}; // namespace Consts
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* BITS_H_ */
