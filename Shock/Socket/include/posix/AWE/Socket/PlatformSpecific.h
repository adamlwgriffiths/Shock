#pragma once

// ---------------------------------------------------------------
// Posix Includes
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

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
typedef int				socket_t;

// ---------------------------------------------------------------
// Global Variables
const int				AWE_INVALID_SOCKET		= -1;

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
