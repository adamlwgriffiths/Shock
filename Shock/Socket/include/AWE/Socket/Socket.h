#pragma once

// ---------------------------------------------------------------
// Socket Includes
#include "AWE/Socket/Platform.h"

// Must come after Platform.h
#include "AWE/Socket/Error.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

void				init();
void				shutdown();

// ---------------------------------------------------------------

class Socket
{
	public:
		// ---------------------------------------------------------------
		// Exceptions
		AWE_DEFINE_EXCEPTION( SocketException );

		// ---------------------------------------------------------------

#if defined(AWE_IPV6_ENABLED)
		static bool				supportsDualStack();
#endif

		// ---------------------------------------------------------------

		Socket();
		Socket( socket_t kSocket );
		virtual ~Socket();

		int						createSocket(
			int iPF,
			int iType,
			int iProtocol
			);
		int						closeSocket();

		AWE::Socket::socket_t	getSocket() const;

		int						setNonBlocking(
			bool bNonBlocking
			);
		int						setReceiveTimeout(
			AWE::uint32 iTimeoutMilliseconds
			);

#if defined(AWE_IPV6_ENABLED)
		// http://msdn.microsoft.com/en-us/library/bb513665(VS.85).aspx
		int						setDualStackSocket( bool bDualStack );
#endif

	protected:
		socket_t			m_kSocket;
};

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
