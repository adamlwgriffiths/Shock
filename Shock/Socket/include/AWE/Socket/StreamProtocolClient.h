#pragma once

// ---------------------------------------------------------------
// Socket Includes
#include "AWE/Socket/ProtocolClient.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

// Stream host has no modifications
template < class T >
class StreamProtocolClient :
	public AWE::Socket::ProtocolClient< T >
{
	public:
		StreamProtocolClient( T* pProtocol ) :
				ProtocolClient< T >( pProtocol )
			{};

		virtual ~StreamProtocolClient()
			{};
};

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
