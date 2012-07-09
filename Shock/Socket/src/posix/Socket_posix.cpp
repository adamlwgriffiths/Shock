#include "AWE/Socket/Socket.h"
// ---------------------------------------------------------------

// System Includes
#include <fcntl.h>

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
	// do nothing
	return;
}

// ---------------------------------------------------------------

void shutdown()
{
	// do nothing
	return;
}


// ---------------------------------------------------------------

#if defined(AWE_IPV6_ENABLED)
bool Socket::supportsDualStack()
{
#if defined(AWE_IP_DUAL_STACK_ENABLED)
	// TODO: detect if kernel supports dual stack
	// for the time being, no love for dual stack =(
	return false;
#else
	return false;
#endif
}
#endif

// ---------------------------------------------------------------

AWE::Socket::Error::_t Socket::closeSocket()
{
	int iResult( ::close( m_kSocket ) );
	m_kSocket = AWE_INVALID_SOCKET;

	if ( iResult != 0 )
	{
		return convertNativeError( iResult );
	}
	return Error::Error_Success;
}

// ---------------------------------------------------------------

AWE::Socket::Error::_t Socket::setNonBlocking(
	bool bNonBlocking
	)
{
	char cNonBlocking( (char)bNonBlocking );

	// a value of 1 for cNonBlocking will activate non-blocking mode
	int iResult = ::ioctl( m_kSocket, FIONBIO, (char *)&cNonBlocking );

	if ( iResult < 0 )
	{
		return convertNativeError( iResult );
	}

	return Error::Error_Success;
}

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
