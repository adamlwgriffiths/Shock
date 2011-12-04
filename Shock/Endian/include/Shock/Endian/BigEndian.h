/*
 * BigEndian.h
 *
 *  Created on: 20/06/2010
 *      Author: Adam Griffiths
 */

#ifndef BIGENDIAN_H_
#define BIGENDIAN_H_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Endian/EndianDefines.h"

// ---------------------------------------------------------------

#if defined( SHOCK_PLATFORM_LITTLE_ENDIAN )
#	error SHOCK_PLATFORM_LITTLE_ENDIAN is defined. Did you include LittleEndian.h previously?
#endif

// ---------------------------------------------------------------
// Define our platform Endian
#define SHOCK_PLATFORM_BIG_ENDIAN

// ---------------------------------------------------------------

namespace Shock {
namespace Platform {
namespace Endian {

// ---------------------------------------------------------------
// Endian
std::string const Description(
	Shock::Consts::Platform::Endian::Big::Description
	);

Shock::Consts::Platform::Endian::_t const Endian(
	Shock::Consts::Platform::Endian::BigEndian
	);

// ---------------------------------------------------------------

}; // namespace Endian
}; // namespace Platform
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* BIGENDIAN_H_ */
