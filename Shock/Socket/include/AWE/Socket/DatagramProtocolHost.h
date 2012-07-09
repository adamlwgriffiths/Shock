#pragma once

// ---------------------------------------------------------------
// Socket Includes
#include "AWE/Socket/ProtocolHost.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

// Datagram host has no modifications
template < class T >
class DatagramProtocolHost :
	public AWE::Socket::ProtocolHost< T >
{
	public:
		DatagramProtocolHost( T* pProtocol ) :
				ProtocolHost< T >( pProtocol )
			{};

		virtual ~DatagramProtocolHost()
			{};
};

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
