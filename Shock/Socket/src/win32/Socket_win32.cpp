#include "AWE/Socket/Socket.h"
// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------
// Global / Static Variables

namespace {
	const AWE::int32		MAX_HOST_LENGTH		= 256;		// http://msdn.microsoft.com/en-us/library/ms738527(VS.85).aspx
};

// ---------------------------------------------------------------

void init()
{
	// Startup winsock version 2.2
	uint8 iMajorVersion( 2 );
	uint8 iMinorVersion( 2 );

	WSADATA wsaData;
	if ( WSAStartup( MAKEWORD(iMajorVersion, iMinorVersion), &wsaData ) != 0 )
	{
		AWE_THROW( AWE::Socket::Socket::SocketException, "Failed to initialise socket library" );
	}

	/*
	 * Confirm that the WinSock DLL supports 2.2.
	 * Note that if the DLL supports versions greater
	 * than 2.2 in addition to 2.2, it will still return
	 * 2.2 in wVersion since that is the version we
	 * requested.
	 */

	if (
		(LOBYTE(wsaData.wVersion) != iMajorVersion) ||
		(HIBYTE(wsaData.wVersion) != iMinorVersion)
		)
	{
		AWE_THROW( AWE::Socket::Socket::SocketException, "Could not find a usable version of Winsock.dll." );
	}
}

// ---------------------------------------------------------------

void shutdown()
{
	// Cleanup winsock
	WSACleanup();
}


// ---------------------------------------------------------------

#if defined(AWE_IPV6_ENABLED)
bool Socket::supportsDualStack()
{
#if defined(AWE_IP_DUAL_STACK_ENABLED)
	// get the windows version
	AWE::uint32 iOS_Version( AWE::Core::Platform::getOperatingSystemVersion() );

	// only vista onward support dual stack
	if ( iOS_Version >= AWE_DEFINE_WINDOWS_VISTA )
	{
		return true;
	}
	return false;
#else
	return false;
#endif
}
#endif

// ---------------------------------------------------------------

int Socket::closeSocket()
{
	int iResult( ::closesocket( m_kSocket ) );
	m_kSocket = AWE_INVALID_SOCKET;
	return iResult;
}

// ---------------------------------------------------------------

int Socket::setNonBlocking(
	bool bNonBlocking
	)
{
	// http://msdn.microsoft.com/en-us/library/ms738573.aspx
	AWE::uint32 iBlocking( (bNonBlocking ? 1 : 0) );	// 0 for non blocking, non-zero for blocking

	// returns non-zero on error
	int iResult(
		::ioctlsocket(
			m_kSocket,	// the socket were modifying
			FIONBIO,	// Non-Blocking I/O
			&iBlocking	// pointer to arg
			)
		);

	return iResult;
}

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
