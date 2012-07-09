#include "AWE/Socket/StreamProtocol.h"
// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

StreamProtocol::StreamProtocol( Socket* pSocket ) :
	Protocol( pSocket ),
	m_pParent( 0 ),
	m_iSocketType( SOCK_STREAM )
{
}

// ---------------------------------------------------------------

StreamProtocol::StreamProtocol( Socket* pSocket, StreamProtocol* pParent ) :
	Protocol( pSocket ),
	m_pParent( pParent ),
	m_iSocketType( SOCK_STREAM )
{
	AWE_ASSERT( m_pParent );
	m_pParent->addChild( this );
}

// ---------------------------------------------------------------

StreamProtocol::~StreamProtocol()
{
	// remove any parent connection
	if ( m_pParent )
	{
		m_pParent->removeChild( this );
		m_pParent = 0;
	}

	// notify our children that we're dying
	StreamSocketContainer::iterator protoIt( m_kChildren.begin() );
	while ( protoIt != m_kChildren.end() )
	{
		AWE::Socket::StreamProtocol* pProtocol = *protoIt;
		AWE_ASSERT( pProtocol );

		pProtocol->removeParent();

		++protoIt;
	}
}

// ---------------------------------------------------------------

int StreamProtocol::getSocketType() const
{
	return m_iSocketType;
}

// ---------------------------------------------------------------

StreamProtocol* StreamProtocol::getParent()
{
	return m_pParent;
}

// ---------------------------------------------------------------

StreamProtocol::StreamSocketContainer::const_iterator StreamProtocol::getChildrenBegin() const
{
	return m_kChildren.begin();
}

// ---------------------------------------------------------------

StreamProtocol::StreamSocketContainer::const_iterator StreamProtocol::getChildrenEnd() const
{
	return m_kChildren.end();
}

// ---------------------------------------------------------------

void StreamProtocol::addChild( StreamProtocol* pChild )
{
	AWE_ASSERT( m_kChildren.find( pChild ) == m_kChildren.end() );
	m_kChildren.insert( pChild );
}

// ---------------------------------------------------------------

void StreamProtocol::removeChild( StreamProtocol* pChild )
{
	AWE_ASSERT( m_kChildren.find( pChild ) != m_kChildren.end() );
	m_kChildren.erase( pChild );
}

// ---------------------------------------------------------------

void StreamProtocol::removeParent()
{
	AWE_ASSERT( m_pParent );
	m_pParent = 0;
}

// ---------------------------------------------------------------

AWE::int32 StreamProtocol::send(
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

AWE::int32 StreamProtocol::receive(
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

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
