#include "AWE/Socket/SocketSelector.h"
// ---------------------------------------------------------------

// Core Includes
#include "AWE/Core/TimeConversion.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

SocketSelector::SocketSelector() :
	m_kReadSet(),
	m_kWriteSet(),
	m_kExceptionSet()
{
}

// ---------------------------------------------------------------

SocketSelector::~SocketSelector()
{
}

// ---------------------------------------------------------------

void SocketSelector::addReadSocket( AWE::Socket::Socket* pSocket )
{
	AWE_CHECK_PTR( pSocket );

	m_kReadSet.addSocket( pSocket );
}

// ---------------------------------------------------------------

void SocketSelector::addWriteSocket( AWE::Socket::Socket* pSocket )
{
	AWE_CHECK_PTR( pSocket );

	m_kWriteSet.addSocket( pSocket );
}

// ---------------------------------------------------------------

void SocketSelector::addExceptionSocket( AWE::Socket::Socket* pSocket )
{
	AWE_CHECK_PTR( pSocket );

	m_kExceptionSet.addSocket( pSocket );
}

// ---------------------------------------------------------------

void SocketSelector::removeReadSocket( AWE::Socket::Socket* pSocket )
{
	AWE_CHECK_PTR( pSocket );

	m_kReadSet.removeSocket( pSocket );
}

// ---------------------------------------------------------------

void SocketSelector::removeWriteSocket( AWE::Socket::Socket* pSocket )
{
	AWE_CHECK_PTR( pSocket );

	m_kWriteSet.removeSocket( pSocket );
}

// ---------------------------------------------------------------

void SocketSelector::removeExceptionSocket( AWE::Socket::Socket* pSocket )
{
	AWE_CHECK_PTR( pSocket );

	m_kExceptionSet.removeSocket( pSocket );
}

// ---------------------------------------------------------------

int SocketSelector::select(
	SocketContainer& kReadSockets,
	SocketContainer& kWriteSockets,
	SocketContainer& kExceptionSockets,
	AWE::uint32& iSocketsSelected,
	AWE::int32 iTimeoutMicros
	)
{
	iSocketsSelected = 0;

	// create timeout
	timeval kTimeout;
	timeval* pTimeout = 0;

	// a NULL pointer is an infinite wait
	// this is indicated by iTimeoutMicros being < 0
	if ( iTimeoutMicros >= 0 )
	{
		AWE::uint32 iSeconds( 0 );
		AWE::uint32 iMicrosRemainer( 0 );
		AWE::Core::TimeConversion::microToSeconds( iTimeoutMicros, iSeconds, iMicrosRemainer );
		kTimeout.tv_sec = iSeconds;
		kTimeout.tv_usec = iMicrosRemainer;
		pTimeout = &kTimeout;
	}

	// determine the highest socket value
	// this is used on POSIX systems
	AWE::uint32 iMaxReadSocket( m_kReadSet.getHighestSocket() );
	AWE::uint32 iMaxWriteSocket( m_kWriteSet.getHighestSocket() );
	AWE::uint32 iMaxExceptionSocket( m_kExceptionSet.getHighestSocket() );

	AWE::uint32 iHighestSocket( iMaxReadSocket );
	if ( iMaxWriteSocket > iHighestSocket )
	{
		iHighestSocket = iMaxWriteSocket;
	}
	if ( iMaxExceptionSocket > iHighestSocket )
	{
		iHighestSocket = iMaxExceptionSocket;
	}

	// we must take a copy of the set to prevent alteration
	// during the select call
	fd_set kReadSet( m_kReadSet.getSet() );
	fd_set kWriteSet( m_kWriteSet.getSet() );
	fd_set kExceptionSet( m_kExceptionSet.getSet() );

	// select any sockets with activity
	// http://msdn.microsoft.com/en-us/library/ms740141(VS.85).aspx
	// http://www.lowtek.com/sockets/select.html
	// http://support.sas.com/documentation/onlinedoc/sasc/doc750/html/lr2/select.htm

	int iResult = ::select(
		(int)iHighestSocket + 1,				// Highest socket value + 1
		&kReadSet,								// read set
		&kWriteSet,								// write set
		&kExceptionSet,							// exception set
		pTimeout								// timeout, Null pointer = infinite wait
		);

	// < 0 indicates error
	// = 0 indicates timeout
	// > 0 indicates the number of sockets that were selected

	// check for success
	if ( iResult > 0 )
	{
		// result will hold the number of sockets that we're set by select

		m_kReadSet.getSetSockets( kReadSockets, kReadSet );
		m_kWriteSet.getSetSockets( kWriteSockets, kWriteSet );
		m_kExceptionSet.getSetSockets( kExceptionSockets, kExceptionSet );

		iSocketsSelected = iResult;
	}

	return iResult;
}

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
