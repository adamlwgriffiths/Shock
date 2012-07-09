#pragma once

// --------------------------------------------------------------
// Core Includes
#include "AWE/Core/Core.h"
#include "AWE/Core/HashSet.h"

// Socket Includes
#include "AWE/Socket/Socket.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

class SocketSet
{
	public:
		// ---------------------------------------------------------------
		// Exceptions
		AWE_DEFINE_EXCEPTION( SocketSetException );

		// ---------------------------------------------------------------
		// Typedefs

		AWE_TYPEDEF_POINTER_HASH_SET( Socket, AWE::Socket::Socket* )		SocketContainer;
/*
		AWE_POINTER_HASH_FUNCTION_DEFINITION(
			Socket,
			AWE::Socket::Socket*
			);

		typedef AWE_STD_EXT::hash_set<
			AWE::Socket::Socket*,
			AWE_POINTER_HASH_FUNCTION_NAME( Socket )
			>		SocketContainer;
*/
		// ---------------------------------------------------------------

		SocketSet();
		~SocketSet();

		void				addSocket( AWE::Socket::Socket* pSocket );
		void				removeSocket( AWE::Socket::Socket* pSocket );
		bool				isSocketInSet( AWE::Socket::Socket* pSocket ) const;

		fd_set				getSet() const;
		AWE::uint32			getHighestSocket() const;
		AWE::uint32			getSetSockets( SocketContainer& kSockets, fd_set const& kSet );

	private:
		void				calculateHighestSocket();

		SocketContainer		m_kSockets;
		fd_set				m_kSet;
		AWE::uint32			m_iHighestSocket;
};

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
