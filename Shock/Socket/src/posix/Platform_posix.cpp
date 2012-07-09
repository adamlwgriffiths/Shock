#include "AWE/Socket/posix/Platform_posix.h"

// ---------------------------------------------------------------

#pragma message( "---------------------------------------------------------------" )
#pragma message( "Build options" )

// ---------------------------------------------------------------

// IPv6
#if defined( AWE_IPV6_ENABLED )
#	pragma message( "IPv6 Enabled" )
#else
#	pragma message( "IPv6 Disabled" )
#endif

// IPv6 Dual-stack
#if defined( AWE_IP_DUAL_STACK_ENABLED )
#	if !defined( AWE_IPV6_ENABLED )
#		error Dual stack enabled without IPv6
#	endif
#	pragma message( "IPv6 Dual Stack Enabled" )
#else
#	pragma message( "IPv6 Dual Stack Disabled" )
#endif

// ---------------------------------------------------------------

#pragma message( "---------------------------------------------------------------" )

// ---------------------------------------------------------------
