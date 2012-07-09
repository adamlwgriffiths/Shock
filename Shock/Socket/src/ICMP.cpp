#include "AWE/Socket/ICMP.h"
// ---------------------------------------------------------------

namespace AWE {
namespace Socket {
namespace ICMP {

// ---------------------------------------------------------------

AWE::Socket::ICMP::Protocol*		create()
{
	return new AWE::Socket::ICMP::Protocol( new Socket() );
}

// ---------------------------------------------------------------

Protocol::Protocol( Socket* pSocket ) :
	AWE::Socket::DatagramProtocol( pSocket ),
	m_iProtocol( 0 )
{
}

// ---------------------------------------------------------------

Protocol::~Protocol()
{
}

// ---------------------------------------------------------------

int Protocol::getProtocol() const
{
	if ( m_iProtocol == 0 )
	{
		AWE_THROW( AWE::Socket::Protocol::ProtocolException, "ICMP has no protocol until the socket is created" );
	}
	return m_iProtocol;
}

// ---------------------------------------------------------------

int Protocol::createSocket( int iAF )
{
	AWE_CHECK_PTR( m_pSocket );
	AWE_ASSERT( m_pSocket->getSocket() == AWE_INVALID_SOCKET );

	m_iProtocol = 0;

	switch( iAF )
	{
		// supported address families
		case AF_UNSPEC:
		case AF_INET:
		{
			// IPv4 ICMP
			m_iProtocol = IPPROTO_ICMP;
		} break;

#if defined(AWE_IPV6_ENABLED)
		case AF_INET6:
		{
			// IPv6 ICMP
			m_iProtocol = IPPROTO_ICMPV6;
		} break;
#endif
		// unsupported address families
		default:
		{
			AWE_THROW( AWE::Socket::Protocol::ProtocolException, "Unsupported address family" );
		} break;
	}

	return m_pSocket->createSocket( iAF, getSocketType(), m_iProtocol );
}

// ---------------------------------------------------------------

int Protocol::resolveLocalAddress(
	Address* pAddress,
	AWE::uint16 iPort,
	int iAF
	)
{
	AWE_CHECK_PTR( pAddress );

	int iResult( 0 );
	int iProtocol( 0 );

	if ( iAF == AF_UNSPEC )
	{
		// because of the separation of ICMP and ICMPv6
		// we need to know the AF before we can continue
		Address kTempAddress;

		// resolve a temporary address using UDP
		iResult = pAddress->resolve(
			iAF,
			IPPROTO_UDP,
			SOCK_DGRAM,
			AI_PASSIVE,
			"",
			iPort
			);
		if ( iResult != 0 )
		{
			return iResult;
		}

		iAF = pAddress->getAddressFamily();
	}

	if ( iAF == AF_INET )
	{
		iProtocol = IPPROTO_ICMP;
	}
	else if ( iAF == AF_INET6 )
	{
		iProtocol = IPPROTO_ICMPV6;
	}
	else
	{
		AWE_THROW( AWE::Socket::Protocol::ProtocolException, "Unknown address family" );
	}

	return pAddress->resolve(
		iAF,
		iProtocol,
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

	int iProtocol( 0 );

	// because of the separation of ICMP and ICMPv6
	// we need to know the AF before we can
	Address kTempAddress;

	// resolve a temporary address using UDP
	int iResult(
		pAddress->resolve(
			AF_UNSPEC,
			IPPROTO_UDP,
			SOCK_DGRAM,
			0,
			sAddress,
			iPort
			)
		);
	if ( iResult != 0 )
	{
		return iResult;
	}

	int iAF = pAddress->getAddressFamily();

	if ( iAF == AF_INET )
	{
		iProtocol = IPPROTO_ICMP;
	}
	else if ( iAF == AF_INET6 )
	{
		iProtocol = IPPROTO_ICMPV6;
	}
	else
	{
		AWE_THROW( AWE::Socket::Protocol::ProtocolException, "Unknown address family" );
	}

	return pAddress->resolve(
		iAF,
		iProtocol,
		getSocketType(),
		0,
		sAddress,
		iPort
		);
}

// ---------------------------------------------------------------

}; // namespace ICMP
}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
