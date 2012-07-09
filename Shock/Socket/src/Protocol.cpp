#include "AWE/Socket/Protocol.h"
// ---------------------------------------------------------------

// System Includes
#include <string.h> /* needed for memset on *nix */

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

Protocol::Protocol( Socket* pSocket ) :
	m_pSocket( pSocket )
{
}

// ---------------------------------------------------------------

Protocol::~Protocol()
{
	if ( m_pSocket->getSocket() != AWE_INVALID_SOCKET )
	{
		m_pSocket->closeSocket();
	}
	AWE_SAFE_DELETE( m_pSocket );
}

// ---------------------------------------------------------------

Socket* Protocol::getSocket() const
{
	return m_pSocket;
}

// ---------------------------------------------------------------

bool Protocol::isValidSocket() const
{
	if ( m_pSocket->getSocket() == AWE_INVALID_SOCKET )
	{
		return false;
	}
	return true;
}

// ---------------------------------------------------------------

int Protocol::getBoundAddress(
	AWE::Socket::Address* pAddress
	)
{
	AWE_CHECK_PTR( m_pSocket );

	// retrieve the bound port
	struct sockaddr_storage kSS;
	socklen_t iSockLength( static_cast< int >( sizeof( kSS ) ) );

	int iResult(
		::getsockname(
			m_pSocket->getSocket(),
			(struct sockaddr*)&kSS,
			&iSockLength
			)
		);

	if ( iResult != 0 )
	{
		return iResult;
	}

	struct sockaddr* pAddr = (struct sockaddr*)&kSS;
	socklen_t iAddrLength( static_cast< socklen_t >( sizeof( kSS ) ) );

	// convert to string
	char pAddressStr[ NI_MAXHOST ];
	char pPortStr[ NI_MAXSERV ];

	memset( pAddressStr, 0, NI_MAXHOST );
	memset( pPortStr, 0, NI_MAXSERV );

	iResult = ::getnameinfo(
		pAddr,
		iAddrLength,
		pAddressStr,
		NI_MAXHOST,
		pPortStr,
		NI_MAXSERV,
		NI_NUMERICHOST | NI_NUMERICSERV
		);

	if ( iResult != 0 )
	{
		return iResult;
	}

	int iSock( atoi( pPortStr ) );

	// convert string to addrinfo
	return pAddress->resolve(
		pAddr->sa_family,
		getProtocol(),
		getSocketType(),
		AI_NUMERICHOST,
		pAddressStr,
		iSock
		);
}

// ---------------------------------------------------------------

int Protocol::createSocket( int iAF )
{
	AWE_CHECK_PTR( m_pSocket );
	AWE_ASSERT( m_pSocket->getSocket() == AWE_INVALID_SOCKET );

	switch( iAF )
	{
		// supported address families
		case AF_UNSPEC:
		case AF_INET:
#if defined(AWE_IPV6_ENABLED)
		case AF_INET6:
#endif
		{
			// do nothing
		} break;

		// unsupported address families
		default:
		{
			AWE_THROW( ProtocolException, "Unsupported address family" );
		} break;
	}

	return m_pSocket->createSocket( iAF, getSocketType(), getProtocol() );
}

// ---------------------------------------------------------------

int Protocol::closeSocket()
{
	AWE_CHECK_PTR( m_pSocket );

	return m_pSocket->closeSocket();
}

// ---------------------------------------------------------------

int Protocol::resolveLocalAddress(
	Address* pAddress,
	AWE::uint16 iPort,
	int iAF
	)
{
	AWE_CHECK_PTR( pAddress );

	return pAddress->resolve(
		iAF,
		getProtocol(),
		getSocketType(),
		AI_PASSIVE,		// local address
		"",
		iPort
		);
}

// ---------------------------------------------------------------

int Protocol::resolveAddress(
	Address* pAddress,
	AWE::Core::String const& sAddress,
	AWE::uint16 iPort
	)
{
	AWE_CHECK_PTR( pAddress );

	return pAddress->resolve(
		AF_UNSPEC,
		getProtocol(),
		getSocketType(),
		0,
		sAddress,
		iPort
		);
}

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
