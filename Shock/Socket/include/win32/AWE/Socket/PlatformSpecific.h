#pragma once

// ---------------------------------------------------------------
// Windows Includes
#include <winsock2.h>
#include <ws2tcpip.h>
#include <wspiapi.h>

// ---------------------------------------------------------------

// IPv6
// Unless IPV6 has been specifically disabled
// Check if our platform supports it and enable / disable
// automatically
#if !defined( AWE_IPV6_DISABLED )
#	if defined( AF_INET6 )//IPPROTO_IPV6 )
#		define AWE_IPV6_ENABLED
#	else
#		define AWE_IPV6_DISABLED
#	endif

// Dual-stack IPv6
#	if defined( IPV6_V6ONLY )
#		define AWE_IP_DUAL_STACK_ENABLED
#	else
#		define AWE_IP_DUAL_STACK_DISABLED
#	endif
#	if defined( IPPROTO_IPV6 )
#		define AWE_IPV6_ENABLED
#	endif
#endif
// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------
// Typedefs
typedef SOCKET			socket_t;
typedef int				socklen_t;

// ---------------------------------------------------------------
// Global Variables
const int				AWE_INVALID_SOCKET		= INVALID_SOCKET;

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
