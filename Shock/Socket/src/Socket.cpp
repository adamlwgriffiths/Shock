#include "AWE/Socket/Socket.h"
// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

Socket::Socket() :
	m_kSocket( AWE_INVALID_SOCKET )
{
}

// ---------------------------------------------------------------

Socket::Socket( socket_t kSocket ) :
	m_kSocket( kSocket )
{
}

// ---------------------------------------------------------------

Socket::~Socket()
{
	if ( m_kSocket != AWE_INVALID_SOCKET )
	{
		AWE_THROW( SocketException, "Socket not shutdown" );
	}
}

// ---------------------------------------------------------------

int Socket::createSocket(
	int iPF,
	int iType,
	int iProtocol
	)
{
	if ( m_kSocket != AWE_INVALID_SOCKET )
	{
		AWE_THROW( SocketException, "Socket already exists" );
	}

	m_kSocket = ::socket(
		iPF,
		iType,
		iProtocol
		);

	if ( m_kSocket == AWE_INVALID_SOCKET )
	{
		return AWE::Socket::Error::getLastNativeError();
	}
	return 0;
}

// ---------------------------------------------------------------

AWE::Socket::socket_t Socket::getSocket() const
{
	return m_kSocket;
}

// ---------------------------------------------------------------

int Socket::setReceiveTimeout(
	AWE::uint32 iTimeoutMilliseconds
	)
{
	int iTimeout( iTimeoutMilliseconds );

	return ::setsockopt(
		m_kSocket,
		SOL_SOCKET,
		SO_RCVTIMEO,
		(char*)&iTimeout,
		sizeof(iTimeout)
		);
}

// ---------------------------------------------------------------

#if defined(AWE_IPV6_ENABLED)
int Socket::setDualStackSocket(
	bool bDualStack
	)
{
	// http://msdn.microsoft.com/en-us/library/bb513665(VS.85).aspx
	AWE::uint32 iProvideHeader(
		(bDualStack ? 0 : 1)	// 0 for dual stack, 1 for normal
		);
	return ::setsockopt(
		m_kSocket,
		IPPROTO_IPV6,
		IPV6_V6ONLY,
		(char*)&iProvideHeader,
		sizeof(iProvideHeader)
		);
}
#endif

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
