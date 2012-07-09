#include "AWE/Socket/SocketSet.h"
// ---------------------------------------------------------------

// Socket Includes
#include "AWE/Socket/Socket.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

SocketSet::SocketSet() :
	m_kSet(),
	m_iHighestSocket( 0 )
{
	FD_ZERO( &m_kSet );
}

// ---------------------------------------------------------------

SocketSet::~SocketSet()
{
	// Assert here if there are any sockets left in our set
	// This is annoying but forcing proper clean up will help
	// prevent dangling pointers causing NULL dereferences
	if ( m_kSockets.size() != 0 )
	{
		AWE_THROW( SocketSetException, "SocketSet destroyed with non-empty socket container" );
	}

	// clear our sets
	FD_ZERO( &m_kSet );

	m_iHighestSocket = 0;
}

// ---------------------------------------------------------------

void SocketSet::addSocket( AWE::Socket::Socket* pSocket )
{
	AWE_CHECK_PTR( pSocket );

	if ( pSocket->getSocket() == AWE_INVALID_SOCKET )
	{
		// throw exception
		AWE_THROW( SocketSetException, "Attempting to add invalid socket to set" );
	}

	// check if the socket already exists in our list
	if ( isSocketInSet( pSocket ) )
	{
		// throw exception
		AWE_THROW( SocketSetException, "Attempted to add duplicate socket to set" );
	}

	m_kSockets.insert( pSocket );

	// add to the set
	FD_SET( pSocket->getSocket(), &m_kSet );

	// update our highest socket
	// this is used for select() on POSIX
	if ( pSocket->getSocket() > m_iHighestSocket )
	{
		m_iHighestSocket = (AWE::uint32)pSocket->getSocket();
	}
}

// ---------------------------------------------------------------

void SocketSet::removeSocket( AWE::Socket::Socket* pSocket )
{
	AWE_CHECK_PTR( pSocket );

	AWE_ASSERT( m_kSockets.find( pSocket ) != m_kSockets.end() );
	m_kSockets.erase( pSocket );

	FD_CLR( pSocket->getSocket(), &m_kSet );

	if ( pSocket->getSocket() == m_iHighestSocket )
	{
		// re-evaluate our highest socket
		calculateHighestSocket();
	}
}

// ---------------------------------------------------------------

bool SocketSet::isSocketInSet( AWE::Socket::Socket* pSocket ) const
{
	return ( m_kSockets.find( pSocket ) != m_kSockets.end() );
}

// ---------------------------------------------------------------

fd_set SocketSet::getSet() const
{
	// return a COPY of the set
	// this prevents alteration
	return m_kSet;
}

// ---------------------------------------------------------------

AWE::uint32 SocketSet::getSetSockets( SocketContainer& kSockets, fd_set const& kSet )
{
	AWE::uint32 iCount( 0 );

	// scan through our sockets
	SocketContainer::iterator sockIt( m_kSockets.begin() );
	while ( sockIt != m_kSockets.end() )
	{
		AWE::Socket::Socket* pSocket = *sockIt;
		AWE_ASSERT( pSocket );

		// if the socket "is set"
		if ( FD_ISSET( pSocket->getSocket(), &kSet ) )
		{
			kSockets.insert( pSocket );
			iCount++;
		}
		++sockIt;
	}

	return iCount;
}

// ---------------------------------------------------------------

AWE::uint32 SocketSet::getHighestSocket() const
{
	return m_iHighestSocket;
}

// ---------------------------------------------------------------

void SocketSet::calculateHighestSocket()
{
	// this is used for select() on POSIX
	// re-evaluate our highest socket
	m_iHighestSocket = 0;

	SocketContainer::const_iterator sockIt( m_kSockets.begin() );
	while ( sockIt != m_kSockets.end() )
	{
		AWE::Socket::Socket* pCurrSocket = *sockIt;
		AWE_ASSERT( pCurrSocket );

		if ( pCurrSocket->getSocket() > m_iHighestSocket )
		{
			m_iHighestSocket = (AWE::uint32)pCurrSocket->getSocket();
		}
		++sockIt;
	}
}

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
