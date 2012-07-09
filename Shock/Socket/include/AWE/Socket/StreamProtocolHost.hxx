
// System Includes
#include <string.h> /* needed for memset on *nix */

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

AWE_TEMPLATE_EXPORT template < class T >
StreamProtocolHost< T >::StreamProtocolHost( T* pProtocol ) :
	ProtocolHost< T >( pProtocol )
{
};

// ---------------------------------------------------------------

AWE_TEMPLATE_EXPORT template < class T >
StreamProtocolHost< T >::~StreamProtocolHost()
{
};

// ---------------------------------------------------------------

AWE_TEMPLATE_EXPORT template < class T >
int StreamProtocolHost< T >::listen(
	AWE::uint32 iMaxPendingConnections
	)
{
	// Mark the socket so it will listen for incoming connections
	// http://msdn.microsoft.com/en-us/library/ms739168(VS.85).aspx
	int iResult(
		::listen(
			ProtocolHost< T >::m_pProtocol->getSocket()->getSocket(),
			iMaxPendingConnections
			)
		);

	return iResult;
};

// ---------------------------------------------------------------

AWE_TEMPLATE_EXPORT template < class T >
int StreamProtocolHost< T >::accept(
	T** pIncomingConnection,
	Address* pAddress
	)
{
	AWE_CHECK_PTR( pIncomingConnection );
	AWE_CHECK_PTR( pAddress );

	// zero the connection pointer
	*pIncomingConnection = 0;

	struct sockaddr_storage kSS;
	socklen_t iSSLength( sizeof( kSS ) );
	memset( &kSS, 0, sizeof( kSS ) );

	// Wait for a connection
	socket_t kNewSocket(
		::accept(
			ProtocolHost< T >::m_pProtocol->getSocket()->getSocket(),
			(struct sockaddr*)&kSS,
			&iSSLength
			)
		);

	// check for errors
	if ( kNewSocket == AWE_INVALID_SOCKET )
	{
		return AWE::Socket::Error::getLastNativeError();
	}

	// wrap the new connection
	Socket* pSocket = new Socket( kNewSocket );

	// set the new protocol wrapper as a child of our new connection
	*pIncomingConnection = new T(
		pSocket,
		ProtocolHost< T >::m_pProtocol
		);

	// convert incoming address to something we can use
	struct sockaddr* pAddr = (struct sockaddr*)&kSS;
	socklen_t iAddrLength( static_cast< socklen_t >( sizeof( kSS ) ) );

	// convert to string
	char pAddressStr[ NI_MAXHOST ];
	char pPortStr[ NI_MAXSERV ];

	memset( pAddressStr, 0, NI_MAXHOST );
	memset( pPortStr, 0, NI_MAXSERV );

	int iResult(
		::getnameinfo(
			pAddr,
			iAddrLength,
			pAddressStr,
			NI_MAXHOST,
			pPortStr,
			NI_MAXSERV,
			NI_NUMERICHOST | NI_NUMERICSERV
			)
		);

	if ( iResult != 0 )
	{
		return iResult;
	}

	int iSock( atoi( pPortStr ) );

	// convert string to addrinfo
	return pAddress->resolve(
		pAddr->sa_family,
		ProtocolHost< T >::m_pProtocol->getProtocol(),
		ProtocolHost< T >::m_pProtocol->getSocketType(),
		AI_NUMERICHOST,
		pAddressStr,
		iSock
		);
};

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
