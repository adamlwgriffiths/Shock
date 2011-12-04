/*
 * Compiler.h
 *
 *  Created on: 20/06/2010
 *      Author: Adam Griffiths
 */

#ifndef COMPILER_H_
#define COMPILER_H_

// ---------------------------------------------------------------
// Ensure we're compiling with Visual Studio
#if !defined( _MSC_VER )
#	error _MSC_VER is not defined. Are you sure youre compiling with Microsoft Visual Studio?
#endif

// ---------------------------------------------------------------
// Standard Includes
#include <string>

// Shock Includes
#include "Shock/Compiler/CompilerOptions.h"
#include "Shock/Types/Types.h"

// ---------------------------------------------------------------

/*!
 * \brief Define our compiler type
 */
#define SHOCK_COMPILER_MSVC

// ---------------------------------------------------------------

namespace Shock {
namespace Consts {
namespace Compiler {
namespace MSVC {

// ---------------------------------------------------------------

namespace Versions
{
	enum _t
	{
		// MS Visual Studio 5
		MSVC_5			= 1100,
		// MS Visual Studio 6
		MSVC_6			= 1200,
		// MS Visual Studio .NET 2002
		MSVC_7			= 1300,
		// MS Visual Studio .NET 2003
		MSVC_71			= 1310,
		// MS Visual Studio 2005
		MSVC_80			= 1400,
		// MS Visual Studio 2008
		MSVC_90			= 1500,
		// MS Visual Studio 2010
		MSVC_100		= 1600,
	};
};

// ---------------------------------------------------------------

std::string const Description(
	"Microsoft Visual Studio"
	);

// ---------------------------------------------------------------
// Specific MSVC version
Shock::Types::uint32_t const Version( _MSC_VER );

// ---------------------------------------------------------------

}; // namespace MSVC
}; // namespace Compiler
}; // namespace Consts
}; // namespace Shock

// ---------------------------------------------------------------

namespace Shock {
namespace Compiler {

// ---------------------------------------------------------------

std::string const Description(
	Shock::Consts::Compiler::MSVC::Description
	);

Shock::Types::uint32_t const Version(
	Shock::Consts::Compiler::MSVC::Version
	);

// ---------------------------------------------------------------

}; // namespace Compiler
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* COMPILER_H_ */
