/*
 * EndianDefines.h
 *
 *  Created on: 20/06/2010
 *      Author: Adam Griffiths
 */

#ifndef ENDIANDEFINES_H_
#define ENDIANDEFINES_H_

// ---------------------------------------------------------------
// Standard Includes
#include <string>

// ---------------------------------------------------------------

namespace Shock {
namespace Consts {
namespace Platform {
namespace Endian {

// ---------------------------------------------------------------

enum _t
{
		BigEndian,
		LittleEndian,
};

// ---------------------------------------------------------------

namespace Little {

// ---------------------------------------------------------------
// Little Endian
std::string const Description(
	"Little Endian"
	);

// ---------------------------------------------------------------

}; // namespace Little

// ---------------------------------------------------------------

namespace Big {

// ---------------------------------------------------------------
// Big Endian
std::string const Description( "Big Endian" );

// ---------------------------------------------------------------

}; // namespace Big

// ---------------------------------------------------------------

}; // namespace Endian
}; // namespace Platform
}; // namespace Consts
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* ENDIANDEFINES_H_ */
