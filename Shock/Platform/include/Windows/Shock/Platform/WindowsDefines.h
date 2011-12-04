/*
 * WindowsDefines.h
 *
 *  Created on: 20/06/2010
 *      Author: adam
 */

#ifndef WINDOWSDEFINES_H_
#define WINDOWSDEFINES_H_

// ---------------------------------------------------------------
// Standard Includes
#include <string.h>

// ---------------------------------------------------------------

namespace Shock {
namespace Consts {
namespace Platform {
namespace Windows {

// ---------------------------------------------------------------
// Platform
std::string const Family(
	"Windows"
	);

// ---------------------------------------------------------------

}; // namespace Windows
}; // namespace Platform
}; // namespace Consts

// ---------------------------------------------------------------

namespace Platform {

// ---------------------------------------------------------------

std::string const Family(
	Shock::Consts::Platform::Windows::Family
	);

// ---------------------------------------------------------------

}; // namespace Platform
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* WINDOWSDEFINES_H_ */
