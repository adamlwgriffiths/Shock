/*
 * WindowsVersions.h
 *
 *  Created on: 20/06/2010
 *      Author: Adam Griffiths
 */

#ifndef WINDOWSVERSIOSHOCK_H_
#define WINDOWSVERSIOSHOCK_H_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Types/Types.h"

// ---------------------------------------------------------------
// Windows versions
// Include the header that includes these #defines or we
// will just be defining our values to nothing!
#include <sdkddkver.h>

// ---------------------------------------------------------------

namespace Shock {
namespace Consts {
namespace Platform {
namespace Windows {

// ---------------------------------------------------------------

Shock::Types::uint32_t const SHOCK_DEFINE_NTTDI_WINDOWS_7(
	NTDDI_WIN7
	);

Shock::Types::uint32_t const SHOCK_DEFINE_NTTDI_WINDOWS_SERVER_2008(
	NTDDI_WS08
	);

Shock::Types::uint32_t const SHOCK_DEFINE_NTTDI_WINDOWS_VISTA_SP1(
	NTDDI_VISTASP1
	);

Shock::Types::uint32_t const SHOCK_DEFINE_NTTDI_WINDOWS_VISTA(
	NTDDI_VISTA
	);

Shock::Types::uint32_t const SHOCK_DEFINE_NTTDI_WINDOWS_SERVER_2003_SP1(
	NTDDI_WS03SP1
	);

Shock::Types::uint32_t const SHOCK_DEFINE_NTTDI_WINDOWS_SERVER_2003(
	NTDDI_WS03
	);

Shock::Types::uint32_t const SHOCK_DEFINE_NTTDI_WINDOWS_XP_SP2(
	NTDDI_WINXPSP2
	);

Shock::Types::uint32_t const SHOCK_DEFINE_NTTDI_WINDOWS_XP_SP1(
	NTDDI_WINXPSP1
	);

Shock::Types::uint32_t const SHOCK_DEFINE_NTTDI_WINDOWS_XP(
	NTDDI_WINXP
	);

Shock::Types::uint32_t const SHOCK_DEFINE_NTTDI_WINDOWS_2000_SP4(
	NTDDI_WIN2KSP4
	);

Shock::Types::uint32_t const SHOCK_DEFINE_NTTDI_WINDOWS_2000_SP3(
	NTDDI_WIN2KSP3
	);

Shock::Types::uint32_t const SHOCK_DEFINE_NTTDI_WINDOWS_2000_SP2(
	NTDDI_WIN2KSP2
	);

Shock::Types::uint32_t const SHOCK_DEFINE_NTTDI_WINDOWS_2000_SP1(
	NTDDI_WIN2KSP1
	);

Shock::Types::uint32_t const SHOCK_DEFINE_NTTDI_WINDOWS_2000(
	NTDDI_WIN2K
	);

// ---------------------------------------------------------------

}; // namespace Windows
}; // namespace Platform
}; // namespace Consts
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* WINDOWSVERSIOSHOCK_H_ */
