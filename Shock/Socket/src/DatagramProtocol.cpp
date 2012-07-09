#include "AWE/Socket/DatagramProtocol.h"
// ---------------------------------------------------------------

// System Includes
#include <string.h> /* needed for memset on *nix */

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

DatagramProtocol::DatagramProtocol( Socket* pSocket ) :
	Protocol( pSocket ),
	m_iSocketType( SOCK_DGRAM )
{
}

// ---------------------------------------------------------------

DatagramProtocol::~DatagramProtocol()
{
}

// ---------------------------------------------------------------

int DatagramProtocol::getSocketType() const
{
	return m_iSocketType;
}

// ---------------------------------------------------------------

AWE::int32 DatagramProtocol::sendTo(
	Address const& kAddress,
	AWE::int8 const* pData,
	AWE::uint32 iLength
	)
{
	if ( kAddress.isValid() == false )
	{
		AWE_THROW( ProtocolException, "Address not resolved" );
	}

	AWE_ASSERT( kAddress.isValid() );
	AWE_CHECK_PTR( kAddress.getAddressInfo() );
	AWE_CHECK_PTR( pData );
	AWE_CHECK_PTR( m_pSocket );
	AWE_ASSERT( m_pSocket->getSocket() != AWE_INVALID_SOCKET );

	addrinfo* pServInfo = kAddress.getAddressInfo();

	int iResult( 0 );

	while ( pServInfo )
	{
		iResult = ::sendto(
			m_pSocket->getSocket(),	// socket
			pData,					// data
			iLength,				// data length
			0,						// flags
			pServInfo->ai_addr,		// address
			(int)pServInfo->ai_addrlen	// address length
			);

		if ( iResult > 0 )
		{
			break;
		}

		pServInfo = pServInfo->ai_next;
	}

	return iResult;
}

// ---------------------------------------------------------------

AWE::int32 DatagramProtocol::receiveFrom(
	Address* pAddress,
	AWE::int8* pData,
	AWE::uint32 iMaxLength
	)
{
	AWE_CHECK_PTR( pAddress );
	AWE_CHECK_PTR( pData );
	AWE_CHECK_PTR( m_pSocket );
	AWE_ASSERT( m_pSocket->getSocket() != AWE_INVALID_SOCKET );

	sockaddr_storage kSS;
	socklen_t iSSLen( sizeof( kSS ) );
	//memset( &kSS, 0, iSSLen );

	// http://msdn.microsoft.com/en-us/library/ms740120(VS.85).aspx
	int iResult(
		::recvfrom(
			m_pSocket->getSocket(),	// socket
			pData,					// buffer
			iMaxLength,				// max buffer length
			0,						// flags
			(struct sockaddr*)&kSS,	// address
			&iSSLen					// address length
			)
		);

	if ( iResult < 0 )
	{
		return iResult;
	}
	else if ( iResult == 0 )
	{
		// 0 indicates connection closed
		return iResult;//(AWE::int32)AWE::Socket::Error::ConnectionClosed;
	}

	// successfully received data
	// convert incoming address to something we can use
	struct sockaddr* pAddr = (struct sockaddr*)&kSS;
	socklen_t iAddrLength( static_cast< socklen_t >( sizeof( kSS ) ) );

	// convert to string
	char pAddressStr[ NI_MAXHOST ];
	char pPortStr[ NI_MAXSERV ];

	memset( pAddressStr, 0, NI_MAXHOST );
	memset( pPortStr, 0, NI_MAXSERV );

	int iResolveResult(
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

	if ( iResolveResult != 0 )
	{
		return iResolveResult;
	}

	int iSock( atoi( pPortStr ) );

	// convert string to addrinfo
	iResolveResult = pAddress->resolve(
		pAddr->sa_family,
		getProtocol(),
		getSocketType(),
		AI_NUMERICHOST,
		pAddressStr,
		iSock
		);

	if ( iResolveResult != 0 )
	{
		return iResolveResult;
	}

	// return the amount of data received
	return iResult;
}

// ---------------------------------------------------------------

AWE::int32 DatagramProtocol::send(
	AWE::int8 const* pData,
	AWE::uint32 iLength
	)
{
	AWE_CHECK_PTR( pData );
	AWE_CHECK_PTR( m_pSocket );
	AWE_ASSERT( m_pSocket->getSocket() != AWE_INVALID_SOCKET );

	int iResult(
		::send(
			m_pSocket->getSocket(),	// socket
			pData,					// data
			iLength,				// data length
			0						// flags
			)
		);

	return iResult;
}

// ---------------------------------------------------------------

AWE::int32 DatagramProtocol::receive(
	AWE::int8* pData,
	AWE::uint32 iMaxLength
	)
{
	AWE_CHECK_PTR( pData );
	AWE_CHECK_PTR( m_pSocket );
	AWE_ASSERT( m_pSocket->getSocket() != AWE_INVALID_SOCKET );

	int iResult(
		::recv(
			m_pSocket->getSocket(),	// socket
			pData,					// buffer
			iMaxLength,				// max buffer length
			0						// flags
			)
		);

	return iResult;
}

// ---------------------------------------------------------------

void DatagramProtocol::setRawSocket( bool bRawSocket )
{
	if ( m_pSocket->getSocket() != AWE_INVALID_SOCKET )
	{
		AWE_THROW( ProtocolException, "Cannot set socket to raw after socket is created" );
	}

	m_iSocketType = (bRawSocket ? SOCK_RAW : SOCK_DGRAM);
}

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
