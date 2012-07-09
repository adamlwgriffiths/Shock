#pragma once

// ---------------------------------------------------------------
// Core Includes
#include "AWE/Core/Core.h"

// Socket Includes
#include "AWE/Socket/SocketSet.h"

// ---------------------------------------------------------------
// Pre-Declarations
namespace AWE {
namespace Socket {
	class Socket;
};
};

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

class SocketSelector
{
	public:
		// ---------------------------------------------------------------
		// Exceptions
		AWE_DEFINE_EXCEPTION( SocketSelectorException );

		// ---------------------------------------------------------------
		// Typedefs

		// this needs to be cross-typedefed or we get conflicting types
		// when SocketSelector attempts to call SocketSet
		typedef AWE::Socket::SocketSet::SocketContainer		SocketContainer;

		// ---------------------------------------------------------------

		SocketSelector();
		~SocketSelector();

		void					addReadSocket( AWE::Socket::Socket* pSocket );
		void					addWriteSocket( AWE::Socket::Socket* pSocket );
		void					addExceptionSocket( AWE::Socket::Socket* pSocket );
		void					removeReadSocket( AWE::Socket::Socket* pSocket );
		void					removeWriteSocket( AWE::Socket::Socket* pSocket );
		void					removeExceptionSocket( AWE::Socket::Socket* pSocket );

		bool					isSocketInReadSet( AWE::Socket::Socket* pSocket );
		bool					isSocketInWriteSet( AWE::Socket::Socket* pSocket );
		bool					isSocketInExceptionSet( AWE::Socket::Socket* pSocket );

		int						select(
			SocketContainer& kReadSockets,
			SocketContainer& kWriteSockets,
			SocketContainer& kExceptionSockets,
			AWE::uint32& iSocketsSelected,
			AWE::int32 iTimeoutMicros = -1
			);

	private:
		SocketSet			m_kReadSet;
		SocketSet			m_kWriteSet;
		SocketSet			m_kExceptionSet;
};

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
