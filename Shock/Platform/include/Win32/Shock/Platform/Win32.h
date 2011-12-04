/*
 * Win32.h
 *
 *  Created on: 20/06/2010
 *      Author: Adam Griffiths
 */

#ifndef WIN32_H_
#define WIN32_H_

// ---------------------------------------------------------------
// Ensure this is a 32-bit build
#if \
	defined( __x86_64__ ) || \
	defined( _M_X64 ) || \
	defined( __powerpc64__ ) || \
	defined( __alpha__ ) || \
	defined( __ia64__ ) || \
	defined( __s390__ ) || \
	defined( __s390x__ )
#	error You cannot compile a 32-bit binary while defines for 64-bit architecture are set.
#endif

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Platform/Bits.h"
#include "Shock/Platform/WindowsDefines.h"

// Standard Includes
#include <string>

// ---------------------------------------------------------------
// Platform Defines
#define SHOCK_PLATFORM_BITS_32

// ---------------------------------------------------------------

namespace Shock {
namespace Consts {
namespace Platform {
namespace Windows {

// ---------------------------------------------------------------

std::string const Description(
	"Windows x86"
	);

// ---------------------------------------------------------------

}; // namespace Windows
}; // namespace Platform
}; // namespace Consts
}; // namespace Shock

// ---------------------------------------------------------------

namespace Shock {
namespace Platform {
namespace Bits {

// ---------------------------------------------------------------

Shock::Consts::Platform::Bits::_t const Bits(
	Shock::Consts::Platform::Bits::Bits32
	);

std::string const Description(
	Shock::Consts::Platform::Bits32::Description
	);

// ---------------------------------------------------------------

}; // namespace Bits

// ---------------------------------------------------------------

std::string const Description(
	Shock::Consts::Platform::Windows::Description
	);

// ---------------------------------------------------------------

}; // namespace Platform
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* WIN32_H_ */
