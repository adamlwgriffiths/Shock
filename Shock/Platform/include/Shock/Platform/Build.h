/*
 * Build.h
 *
 *  Created on: 29/06/2010
 *      Author: adam
 */

#ifndef BUILD_H_
#define BUILD_H_

// ---------------------------------------------------------------
// Standard Includes
#include <string>

// ---------------------------------------------------------------

#if defined( DEBUG ) || defined( _DEBUG )
#	if !defined( SHOCK_BUILD_DEBUG )
#		define SHOCK_BUILD_DEBUG
#	endif
#elif defined( NDEBUG ) || defined( _NDEBUG )
# if !defined( SHOCK_BUILD_RELEASE )
#		define SHOCK_BUILD_RELEASE
#	endif
#endif

// ---------------------------------------------------------------

namespace Shock {
namespace Consts {
namespace Build {

// ---------------------------------------------------------------

enum _t
{
		DebugBuild,
		ReleaseBuild,
};

// ---------------------------------------------------------------

namespace Debug {
std::string const Description(
	"Debug"
	);
}; // namespace Debug

// ---------------------------------------------------------------

namespace Release {
std::string const Description(
	"Release"
	);
}; // namespace Release

// ---------------------------------------------------------------

}; // namespace Build
}; // namespace Consts
}; // namespace Shock

// ---------------------------------------------------------------

namespace Shock {
namespace Build {

// ---------------------------------------------------------------

#if defined( SHOCK_BUILD_DEBUG )

// Debug build
Shock::Consts::Build::_t const Build(
	Shock::Consts::Build::DebugBuild
	);

std::string const Description(
	Shock::Consts::Build::Debug::Description
	);

#elif defined( SHOCK_BUILD_RELEASE )

// Release build
Shock::Consts::Build::_t const Build(
	Shock::Consts::Build::ReleaseBuild
	);

std::string const Description(
	Shock::Consts::Build::Release::Description
	);

#endif

// ---------------------------------------------------------------

}; // namespace Build
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* BUILD_H_ */
