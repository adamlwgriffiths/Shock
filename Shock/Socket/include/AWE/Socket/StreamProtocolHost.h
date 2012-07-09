#pragma once

// ---------------------------------------------------------------
// Socket Includes
#include "AWE/Socket/ProtocolHost.h"

// Standard Includes
#include <stdlib.h>

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

template < class T >
class StreamProtocolHost :
	public AWE::Socket::ProtocolHost< T >
{
	public:
		StreamProtocolHost( T* pProtocol );
		virtual ~StreamProtocolHost();

		int							listen(
			AWE::uint32 iMaxPendingConnections = 30
			);
		int							accept(
			T** pIncomingConnection,
			Address* pAddress
			);
};

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------

#ifndef AWE_TEMPLATE_EXPORT_KEYWORD
#	include "StreamProtocolHost.hxx"
#endif

// ---------------------------------------------------------------
