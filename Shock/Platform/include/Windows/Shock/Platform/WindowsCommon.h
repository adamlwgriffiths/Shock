/*
 * WindowsCommon.h
 *
 *  Created on: 20/06/2010
 *      Author: adam
 */

#ifndef WINDOWSCOMMON_H_
#define WINDOWSCOMMON_H_

// ---------------------------------------------------------------
// Define our Windows platform Includes
#define SHOCK_PLATFORM_WINDOWS

// ---------------------------------------------------------------
// Define for windows to know which OS we're compiling for
// we support at a minimum Windows XP SP 2
#if !defined( _WIN32_WINNT )
#	define _WIN32_WINNT											SHOCK_DEFINE_NTTDI_WINDOWS_XP_SP2
#endif

// ---------------------------------------------------------------
// Windows Includes
// Include after _WIN32_WINNT define
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// ---------------------------------------------------------------

#endif /* WINDOWSCOMMON_H_ */
