/*
 * LittleEndian.h
 *
 *  Created on: 20/06/2010
 *      Author: Adam Griffiths
 */

#ifndef LITTLEENDIAN_H_
#define LITTLEENDIAN_H_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Endian/EndianDefines.h"

// ---------------------------------------------------------------

#if defined( SHOCK_PLATFORM_BIG_ENDIAN )
#	error SHOCK_PLATFORM_BIG_ENDIAN is defined. Did you include BigEndian.h previously?
#endif

// ---------------------------------------------------------------
// Define our platform Endian
#define SHOCK_PLATFORM_LITTLE_ENDIAN

// ---------------------------------------------------------------

namespace Shock {
namespace Platform {
namespace Endian {

// ---------------------------------------------------------------
// Endian
std::string const Description(
	Shock::Consts::Platform::Endian::Little::Description
	);

Shock::Consts::Platform::Endian::_t const Endian(
	Shock::Consts::Platform::Endian::LittleEndian
	);

// ---------------------------------------------------------------

}; // namespace Endian
}; // namespace Platform
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* LITTLEENDIAN_H_ */
