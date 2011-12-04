/*
 * Compiler.h
 *
 *  Created on: 20/06/2010
 *      Author: Adam Griffiths
 */

#ifndef COMPILER_H_
#define COMPILER_H_

// ---------------------------------------------------------------
// Ensure we're compiling with MinGW
#if !defined( __GNUC__ )
#	error __GNUC__ is not defined. Are you sure youre compiling with MinGW?
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
#define SHOCK_COMPILER_MINGW

// ---------------------------------------------------------------

namespace Shock {
namespace Consts {
namespace Compiler {
namespace MinGW {

// ---------------------------------------------------------------

std::string const Description(
	"MinGW"
	);

// ---------------------------------------------------------------
// Specific MinGW version
Shock::Types::uint32_t const Version(
	(__GNUC__ * 100000) +
	(__GNUC_MINOR__ * 1000) +
	__GNUC_PATCHLEVEL__
	);

// ---------------------------------------------------------------

}; // namespace MinGW
}; // namespace Compiler
}; // namespace Consts
}; // namespace Shock

// ---------------------------------------------------------------

namespace Shock {
namespace Compiler {

// ---------------------------------------------------------------

std::string const Description(
	Shock::Consts::Compiler::MinGW::Description
	);

Shock::Types::uint32_t const Version(
	Shock::Consts::Compiler::MinGW::Version
	);

// ---------------------------------------------------------------

}; // namespace Compiler
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* COMPILER_H_ */
