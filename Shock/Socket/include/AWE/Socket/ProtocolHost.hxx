
// ---------------------------------------------------------------
// Socket Includes
#include "AWE/Socket/Address.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

AWE_TEMPLATE_EXPORT template < class T >
ProtocolHost< T >::ProtocolHost( T* pProtocol ) :
	m_pProtocol( pProtocol )
{
	AWE_CHECK_PTR( pProtocol );
};

// ---------------------------------------------------------------

AWE_TEMPLATE_EXPORT template < class T >
ProtocolHost< T >::~ProtocolHost()
{
	m_pProtocol = 0;
};

// ---------------------------------------------------------------

AWE_TEMPLATE_EXPORT template < class T >
int ProtocolHost< T >::bind(
	int iAF,
	AWE::uint16 iPort
	)
{
	int iResult( -1 );

	// Bind
	if ( iAF == AF_INET )
	{
		struct sockaddr_in local;
		local.sin_family = AF_INET;
		local.sin_addr.s_addr = INADDR_ANY;
		local.sin_port = htons( iPort );

		iResult = ::bind(
			m_pProtocol->getSocket()->getSocket(),
			(struct sockaddr*)&local,
			sizeof(local)
			);
	}
#if defined(AWE_IPV6_ENABLED)
	else if ( iAF == AF_INET6 )
	{
		struct in6_addr addr = IN6ADDR_ANY_INIT;
		struct sockaddr_in6 local;
		local.sin6_family = AF_INET6;
		local.sin6_addr = addr;
		local.sin6_port = htons( iPort );

		iResult = ::bind(
			m_pProtocol->getSocket()->getSocket(),
			(struct sockaddr*)&local,
			sizeof(local)
			);
	}
#endif
	else
	{
		AWE_THROW( ProtocolHostException, "Unknown Address Family" );
	}

	// we cannot update the address we've bound
	// to in-case we were given an un-specified address
	// http://msdn.microsoft.com/en-us/library/ms738532(VS.85).aspx

	return iResult;
};

// ---------------------------------------------------------------

AWE_TEMPLATE_EXPORT template < class T >
int ProtocolHost< T >::bind(
	Address const& kAddress
	)
{
	int iResult( 0 );

	if ( kAddress.isValid() == false )
	{
		AWE_THROW( ProtocolHostException, "Address not resolved" );
	}

	addrinfo* pCurrAddr = kAddress.getAddressInfo();
	AWE_CHECK_PTR( pCurrAddr );

	while ( pCurrAddr )
	{
		// Bind to the local address
		int iResult = ::bind(
			m_pProtocol->getSocket()->getSocket(),
			pCurrAddr->ai_addr,
			(int)pCurrAddr->ai_addrlen
			);

		// check for success
		if ( iResult == 0 )
		{
			// we cannot update the address we've bound
			// to in-case we were given an un-specified address
			// http://msdn.microsoft.com/en-us/library/ms738532(VS.85).aspx
			break;
		}

		pCurrAddr = pCurrAddr->ai_next;
	}

	return iResult;
};

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
