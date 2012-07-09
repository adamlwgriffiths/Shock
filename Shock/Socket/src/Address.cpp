#include "AWE/Socket/Address.h"
// ---------------------------------------------------------------

// Core Includes
#include "AWE/Core/TypeConversion.h"

// System Includes
#include <string.h> /* needed for memset on *nix */

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

Address::Address() :
	m_pAddrInfo( 0 )
{
}

// ---------------------------------------------------------------

Address::Address( addrinfo* pAddrInfo ) :
	m_pAddrInfo( pAddrInfo )
{
}

// ---------------------------------------------------------------

Address::~Address()
{
	if ( m_pAddrInfo != 0 )
	{
		freeaddrinfo( m_pAddrInfo );
		m_pAddrInfo = 0;
	}
}

// ---------------------------------------------------------------

bool Address::isValid() const
{
	if ( m_pAddrInfo != 0 )
	{
		return true;
	}
	return false;
}

// ---------------------------------------------------------------

addrinfo* Address::getAddressInfo() const
{
	return m_pAddrInfo;
}

// ---------------------------------------------------------------

int Address::getAddressFamily() const
{
	if ( m_pAddrInfo == 0 )
	{
		AWE_THROW( AddressException, "Address not resolved" );
	}

	return m_pAddrInfo->ai_family;
}

// ---------------------------------------------------------------

int Address::getAddress(
	AWE::Core::String* pAddress
	)
{
	if ( m_pAddrInfo == 0 )
	{
		AWE_THROW( AddressException, "Address not resolved" );
	}

	AWE_CHECK_PTR( pAddress );

	*pAddress = "";

	return reverseLookup(
		NI_NUMERICHOST |		// don't resolve the host
		NI_NUMERICSERV,			// resolve the port
		pAddress,
		0
		);
}

// ---------------------------------------------------------------

int Address::getPort(
	AWE::uint16* pPort
	) const
{
	if ( m_pAddrInfo == 0 )
	{
		AWE_THROW( AddressException, "Address not resolved" );
	}

	AWE_CHECK_PTR( pPort );

	*pPort = 0;

	return reverseLookup(
		NI_NUMERICHOST |		// don't resolve the host
		NI_NUMERICSERV,			// resolve the port
		0,
		pPort
		);
}

// ---------------------------------------------------------------

int Address::lookupHostname(
	AWE::Core::String* pHostname
	)
{
	if ( m_pAddrInfo == 0 )
	{
		AWE_THROW( AddressException, "Address not resolved" );
	}

	AWE_CHECK_PTR( pHostname );

	*pHostname = "";

	return reverseLookup(
		NI_NUMERICSERV,			// resolve the port
		pHostname,
		0
		);
}

// ---------------------------------------------------------------

int Address::resolve(
	int iAF,
	int iProtocol,
	int iSockType,
	int iFlags,
	AWE::Core::String const& sAddress,
	AWE::uint16 iPort
	)
{
	addrinfo kHints;
	memset( &kHints, 0, sizeof( kHints ) );		// make sure the struct is empty

	kHints.ai_family		= iAF;				// Address Family
	kHints.ai_protocol		= iProtocol;		// Protocol
	kHints.ai_socktype		= iSockType;		// Socket Type
	kHints.ai_flags			= iFlags;			// Flags

	return resolve( &kHints, sAddress, iPort );
}

// ---------------------------------------------------------------

int Address::resolve(
	addrinfo* pHints,
	AWE::Core::String const& sAddress,
	AWE::uint16 iPort
	)
{
	AWE_CHECK_PTR( pHints );

	if ( m_pAddrInfo != 0 )
	{
		freeaddrinfo( m_pAddrInfo );
		m_pAddrInfo = 0;
	}

	char const* pAddress = 0;
	char const* pPort = 0;

	// check if the address is empty
	if ( sAddress.length() != 0 )
	{
		pAddress = sAddress.c_str();
	}

	AWE::Core::String sPort;
	// always provide the port even if it's 0
	{
		AWE::Core::TypeConversion::toString< AWE::uint16 >( iPort, sPort );
		pPort = sPort.c_str();
	}

	// resolve our host and populate our address info
	return ::getaddrinfo(
		pAddress,				// local interface, NULL indicates any local interface
		pPort,					// local port
		pHints,					// protocol hints
		&m_pAddrInfo			// result
		);
}

// ---------------------------------------------------------------

int Address::reverseLookup(
	int iLookupFlags,
	AWE::Core::String* pHostname,
	AWE::uint16* pPort
	) const
{
	if ( m_pAddrInfo == 0 )
	{
		AWE_THROW( AddressException, "Address not resolved" );
	}

	char pAddressStr[ NI_MAXHOST ];
	char pPortStr[ NI_MAXSERV ];

	memset( pAddressStr, 0, NI_MAXHOST );
	memset( pPortStr, 0, NI_MAXSERV );

	// http://www.breakingrobots.net/blog/2005/09/13.html
	// http://msdn.microsoft.com/en-us/library/ms738532(VS.85).aspx
	// Setting the NI_NUMERICHOST flag returns the numeric form of the host name instead
	// of its name, a reverse DNS lookup. The numeric form of the host name is also
	// returned if the host name cannot be resolved by DNS.
	//
	// Setting the NI_NUMERICSERV flag returns the port number of the service instead
	// of its name. Also, if a host name is not found for an IP address (127.0.0.2, for
	// example), the hostname is returned as the IP address.

	int iResult(
		::getnameinfo(
			m_pAddrInfo->ai_addr,
			static_cast< socklen_t >( m_pAddrInfo->ai_addrlen ),
			pAddressStr,
			NI_MAXHOST,
			pPortStr,
			NI_MAXSERV,
			iLookupFlags			// the flags
			)
		);

	if ( iResult != 0 )
	{
		return iResult;
	}

	if ( pHostname != 0 )
	{
		*pHostname = pAddressStr;
	}
	if ( pPort != 0 )
	{
		AWE::Core::String sTemp( pPortStr );
		AWE::Core::TypeConversion::fromString< AWE::uint16 >(
			sTemp,
			*pPort,
			std::ios_base::dec
			);
	}

	return iResult;
}

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
