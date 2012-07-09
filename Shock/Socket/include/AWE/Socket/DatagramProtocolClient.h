#pragma once

// ---------------------------------------------------------------
// Socket Includes
#include "AWE/Socket/ProtocolClient.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

// Datagram host has no modifications
template < class T >
class DatagramProtocolClient :
	public AWE::Socket::ProtocolClient< T >
{
	public:
		DatagramProtocolClient( T* pProtocol ) :
				ProtocolClient< T >( pProtocol )
			{};

		virtual ~DatagramProtocolClient()
			{};
};

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
