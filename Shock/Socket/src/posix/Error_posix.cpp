#include "AWE/Socket/Error.h"
// ---------------------------------------------------------------

// Socket Includes
#include "AWE/Socket/Platform.h"
#include "AWE/Socket/Socket.h"

// Posix Includes
#include <errno.h>

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------
AWE::Socket::Error::_t convertNativeError( int iError )
{
	switch( iError )
	{
#if defined( EWOULDBLOCK )
		case EWOULDBLOCK:
#else
		case EAGAIN:
#endif
		// The socket is marked non-blocking and no connections are present
		// to be accepted.
		{
			return AWE::Socket::Error::Error_WouldBlock;
		} break;

		case EBADF:
		// The descriptor is invalid.
		{
			return AWE::Socket::Error::Error_InvalidSocket;
		} break;

		case ECONNABORTED:
		// A connection has been aborted.
		{
			return AWE::Socket::Error::Error_ConnectionClosed;
		} break;

		case EFAULT:
		// The addr argument is not in a writable part of the user address
		// space.
		{
			return AWE::Socket::Error::Error_InvalidOperation;
		} break;

		case EINTR:
		// The system call was interrupted by a signal that was caught
		// before a valid connection arrived; see signal(7).
		{
			return AWE::Socket::Error::Error_TryAgain;
		} break;

		case EINVAL:
		// Socket is not listening for connections, or addrlen is invalid
		// (e.g., is negative).
		// (accept4()) invalid value in flags.
		{
			return AWE::Socket::Error::Error_InvalidOperation;
		} break;

		case EMFILE:
		// The per-process limit of open file descriptors has been reached.
		{
			return AWE::Socket::Error::Error_InsufficientResources;
		} break;

		case ENFILE:
		// The system limit on the total number of open files has been
		// reached.
		{
			return AWE::Socket::Error::Error_InsufficientResources;
		} break;

		case ENOBUFS:
		// Not enough free memory. This often means that the memory
		// allocation is limited by the socket buffer limits, not by
		// the system memory.
		{
			// Same as ENOMEM
			return AWE::Socket::Error::Error_InsufficientResources;
		} break;

		case ENOMEM:
		// Not enough free memory. This often means that the memory
		// allocation is limited by the socket buffer limits, not by
		// the system memory.
		{
			return AWE::Socket::Error::Error_InsufficientResources;
		} break;

		case ENOTSOCK:
		// The descriptor references a file, not a socket.
		{
			return AWE::Socket::Error::Error_InvalidSocket;
		} break;

		case EOPNOTSUPP:
		// The referenced socket is not of type SOCK_STREAM.
		{
			return AWE::Socket::Error::Error_InvalidOperation;
		} break;

		case EPROTO:
		// Protocol error.
		{
			return AWE::Socket::Error::Error_InvalidOperation;
		} break;

		case EPERM:
		// Firewall rules forbid connection.
		{
			return AWE::Socket::Error::Error_ConnectionRefused;
		} break;

		case ENOSR:
		// No stream buffers available
		{
			return AWE::Socket::Error::Error_InsufficientResources;
		} break;

		case ESOCKTNOSUPPORT:
		{
			return AWE::Socket::Error::Error_NotSupported;
		} break;

		case EPROTONOSUPPORT:
		{
			return AWE::Socket::Error::Error_NotSupported;
		} break;

#if defined( ERESTARTSYS )
		case ERESTARTSYS:
		{
			return AWE::Socket::Error::Error_NetworkDown;
		} break;
#endif

		case EACCES:
		// The address is protected, and the user is not the superuser.
		// OR for UNIX sockets
		// Search permission is denied on a component of the path prefix.
		{
			return AWE::Socket::Error::Error_InvalidAddress;
		} break;

        case EADDRINUSE:
		// The given address is already in use.
		{
			return AWE::Socket::Error::Error_AddressInUse;
		} break;

        case EADDRNOTAVAIL:
		// A nonexistent interface was requested or the requested address
		// was not local.
		{
			return AWE::Socket::Error::Error_InvalidAddress;
		} break;

        case ELOOP:
        // Too many symbolic links were encountered in resolving addr.
        {
			return AWE::Socket::Error::Error_InvalidAddress;
        } break;

        case ENAMETOOLONG:
		// addr is too long.
		{
			return AWE::Socket::Error::Error_InvalidAddress;
        } break;

        case ENOENT:
        // The file does not exist.
        {
			return AWE::Socket::Error::Error_InvalidAddress;
        } break;

		case ENOTCONN:
		// The socket is associated with a connection-oriented protocol and
		// has not been connected (see connect(2) and accept(2)).
		{
			return AWE::Socket::Error::Error_InvalidOperation;
		} break;

		case EDESTADDRREQ:
		// The socket is not connection-mode, and no peer address is set.
		{
			return AWE::Socket::Error::Error_InvalidOperation;
		} break;

        case ENOTDIR:
		// A component of the path prefix is not a directory.
		{
			return AWE::Socket::Error::Error_InvalidAddress;
        } break;

        case EROFS:
        // The socket inode would reside on a read-only file system.
        // SVr4, 4.4BSD, POSIX.1-2001 (bind() first appeared in 4.2BSD).
        {
			return AWE::Socket::Error::Error_InvalidSocket;
        } break;

        case EAFNOSUPPORT:
		// The passed address didn’t have the correct address family in its
		// sa_family field.
		{
			return AWE::Socket::Error::Error_NotSupported;
		} break;

        case EALREADY:
		// The socket is non-blocking and a previous connection attempt has
		// not yet been completed.
		{
			return AWE::Socket::Error::Error_OperationInProgress;
		} break;

        case ECONNREFUSED:
		// No-one listening on the remote address.
		{
			return AWE::Socket::Error::Error_ConnectionRefused;
		} break;

        case EINPROGRESS:
		// The socket is non-blocking and the connection cannot be com‐
		// pleted immediately. It is possible to select(2) or poll(2)  for
		// completion by selecting the socket for writing. After select(2)
		// indicates writability, use getsockopt(2) to read the SO_ERROR
		// option at level SOL_SOCKET to determine whether connect()
		// completed successfully (SO_ERROR is zero) or unsuccessfully
		// (SO_ERROR is one of the usual error codes listed here,
		// explaining the reason for the failure).
		{
			return AWE::Socket::Error::Error_OperationInProgress;
		} break;

        case EISCONN:
		// The socket is already connected.
		{
			return AWE::Socket::Error::Error_InvalidOperation;
		} break;

        case ENETUNREACH:
		// Network is unreachable.
		{
			return AWE::Socket::Error::Error_NetworkDown;
		} break;

        case ETIMEDOUT:
		// Timeout while attempting connection. The server may be too busy
		// to accept new connections. Note that for IP sockets the timeout
		// may be very long when syncookies are enabled on the server.
        // SVr4, 4.4BSD, (the connect() function first appeared in 4.2BSD),
        // POSIX.1-2001.
        {
			return AWE::Socket::Error::Error_Timeout;
		} break;

		case EMSGSIZE:
		// The socket type requires that message be  sent  atomically,  and
		// the size of the message to be sent made this impossible.
		{
			return AWE::Socket::Error::Error_MessageTooBig;
		} break;

		case EPIPE:
		// The local end has been shut down on a connection oriented
		// socket. In this case the process will also receive a SIGPIPE
		// unless MSG_NOSIGNAL is set.
        // 4.4BSD, SVr4, POSIX.1-2001. These function calls appeared in 4.2BSD.
        {
			return AWE::Socket::Error::Error_ConnectionClosed;
		} break;

		case EIO:
		// An I/O error occurred.
        // SVr4, 4.3BSD, POSIX.1-2001.
        {
			return AWE::Socket::Error::Error_Failure;
		} break;


		default:
		{
			// unknown error
			// signal generic failure
			return AWE::Socket::Error::Error_Failure;
		} break;
	}
}

// ---------------------------------------------------------------

void getErrorString( int iError, AWE::Core::String& sString )
{
	switch( iError )
	{
#if defined( EWOULDBLOCK )
		case EWOULDBLOCK:
#else
		case EAGAIN:
#endif
		// The socket is marked non-blocking and no connections are present
		// to be accepted.
		{
			sString = "EWOULDBLOCK - Non-blocking socket operation";
		} break;

		case EBADF:
		// The descriptor is invalid.
		{
			sString = "EBADF - Invalid file descriptor";
		} break;

		case ECONNABORTED:
		// A connection has been aborted.
		{
			sString = "ECONNABORTED - Connection aborted";
		} break;

		case EFAULT:
		// The addr argument is not in a writable part of the user address
		// space.
		{
			sString = "EFAULT - Invalid parameter";
		} break;

		case EINTR:
		// The system call was interrupted by a signal that was caught
		// before a valid connection arrived; see signal(7).
		{
			sString = "EINTR - System call interrupted by a signal";
		} break;

		case EINVAL:
		// Socket is not listening for connections, or addrlen is invalid
		// (e.g., is negative).
		// (accept4()) invalid value in flags.
		{
			sString = "EINVAL - Socket is in an invalid state for operation or addrlen is invalid or invalid value in flags";
		} break;

		case EMFILE:
		// The per-process limit of open file descriptors has been reached.
		{
			sString = "EMFILE - Too many open files";
		} break;

		case ENFILE:
		// The system limit on the total number of open files has been
		// reached.
		{
			sString = "ENFILE - System limit of total number of open files reached";
		} break;

		case ENOBUFS:
		// Not enough free memory. This often means that the memory
		// allocation is limited by the socket buffer limits, not by
		// the system memory.
		{
			// Same as ENOMEM
			sString = "ENOBUFS - Not enough free memory or socket buffer limits reached";
		} break;

		case ENOMEM:
		// Not enough free memory. This often means that the memory
		// allocation is limited by the socket buffer limits, not by
		// the system memory.
		{
			sString = "ENOMEM - Not enough free memory or socket buffer limits reached";
		} break;

		case ENOTSOCK:
		// The descriptor references a file, not a socket.
		{
			sString = "ENOTSOCK - Descriptor is a file, not a socket";
		} break;

		case EOPNOTSUPP:
		// The referenced socket is not of type SOCK_STREAM.
		{
			sString = "EOPNOTSUPP - Socket type not supported by this operation";
		} break;

		case EPROTO:
		// Protocol error.
		{
			sString = "EPROTO - Protocol error";
		} break;

		case EPERM:
		// Firewall rules forbid connection.
		{
			sString = "EPERM - Socket broadcast flag not set or Connection forbidden by firewall";
		} break;

		case ENOSR:
		// No stream buffers available
		{
			sString = "ENOSR - No stream buffers available";
		} break;

		case ESOCKTNOSUPPORT:
		{
			sString = "ESOCKTNOSUPPORT - Socket type not supported";
		} break;

		case EPROTONOSUPPORT:
		{
			sString = "EPROTONOSUPPORT - Protocol not supported";
		} break;

#if defined( ERESTARTSYS )
		case ERESTARTSYS:
		{
			sString = "ERESTARTSYS - System going down for restart";
		} break;
#endif

		case EACCES:
		// The address is protected, and the user is not the superuser.
		// OR for UNIX sockets
		// Search permission is denied on a component of the path prefix.
		{
			sString = "EACCES - Insufficient privileges or socket broadcast flag not set or Connection forbidden by firewall";
		} break;

        case EADDRINUSE:
		// The given address is already in use.
		{
			sString = "EADDRINUSE - Address already in use";
		} break;

        case EADDRNOTAVAIL:
		// A nonexistent interface was requested or the requested address
		// was not local.
		{
			sString = "EADDRNOTAVAIL - Interface does not exist or address is not local";
		} break;

        case ELOOP:
        // Too many symbolic links were encountered in resolving addr.
        {
        	sString = "ELOOP - Too many symbolic links while trying to resolve address";
        } break;

        case ENAMETOOLONG:
		// addr is too long.
		{
			sString = "ENAMETOOLONG - addr is too long";
        } break;

        case ENOENT:
        // The file does not exist.
        {
        	sString = "ENOENT - File does not exist";
        } break;

		case ENOTCONN:
		// The socket is associated with a connection-oriented protocol and
		// has not been connected (see connect(2) and accept(2)).
		{
			sString = "ENOTCONN - Connection-oriented socket is not connected";
		} break;

		case EDESTADDRREQ:
		// The socket is not connection-mode, and no peer address is set.
		{
			sString = "EDESTADDRREQ - Socket is not connected and no address is set";
		} break;



        case ENOTDIR:
		// A component of the path prefix is not a directory.
		{
			sString = "ENOTDIR - Component of path prefix is not a directory";
        } break;

        case EROFS:
        // The socket inode would reside on a read-only file system.
        // SVr4, 4.4BSD, POSIX.1-2001 (bind() first appeared in 4.2BSD).
        {
			sString = "EROFS - Socket resides on read-only file system";
        } break;

        case EAFNOSUPPORT:
		// The passed address didn’t have the correct address family in its
		// sa_family field.
		{
			sString = "EAFNOSUPPORT - Address Family not supported";
		} break;

        case EALREADY:
		// The socket is non-blocking and a previous connection attempt has
		// not yet been completed.
		{
			sString = "EALREADY - Non-blocking socket has previous attempt in progress";
		} break;

        case ECONNREFUSED:
		// No-one listening on the remote address.
		{
			sString = "ECONNREFUSED - Connection refused";
		} break;

        case EINPROGRESS:
		// The socket is non-blocking and the connection cannot be com‐
		// pleted immediately. It is possible to select(2) or poll(2)  for
		// completion by selecting the socket for writing. After select(2)
		// indicates writability, use getsockopt(2) to read the SO_ERROR
		// option at level SOL_SOCKET to determine whether connect()
		// completed successfully (SO_ERROR is zero) or unsuccessfully
		// (SO_ERROR is one of the usual error codes listed here,
		// explaining the reason for the failure).
		{
			sString = "EINPROGRESS - The socket is non-blocking and the connection cannot be completed immediately";
		} break;

        case EISCONN:
		// The socket is already connected.
		{
			sString = "EISCONN - Socket is already connected";
		} break;

        case ENETUNREACH:
		// Network is unreachable.
		{
			sString = "ENETUNREACH - Network unreachable";
		} break;

        case ETIMEDOUT:
		// Timeout while attempting connection. The server may be too busy
		// to accept new connections. Note that for IP sockets the timeout
		// may be very long when syncookies are enabled on the server.
        // SVr4, 4.4BSD, (the connect() function first appeared in 4.2BSD),
        // POSIX.1-2001.
        {
        	sString = "ETIMEDOUT - Operation timed out";
		} break;

		case EMSGSIZE:
		// The socket type requires that message be  sent  atomically,  and
		// the size of the message to be sent made this impossible.
		{
        	sString = "EMSGSIZE - Message is too big";
		} break;

		case EPIPE:
		// The local end has been shut down on a connection oriented
		// socket. In this case the process will also receive a SIGPIPE
		// unless MSG_NOSIGNAL is set.
        // 4.4BSD, SVr4, POSIX.1-2001. These function calls appeared in 4.2BSD.
        {
        	sString = "EPIPE - Local end of connection oriented socket has been closed";
		} break;

		case EIO:
		// An I/O error occurred.
        // SVr4, 4.3BSD, POSIX.1-2001.
        {
        	sString = "EIO - An IO error occurred";
		} break;


		default:
		{
			// unknown error
			// signal generic failure
			sString = "Unknown error";
		} break;
	}
}
// ---------------------------------------------------------------

int getLastNativeError()
{
	// http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html#errnoman
	return errno;
}

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
