#pragma once

// ---------------------------------------------------------------
// Core Includes
#include "AWE/Core/Core.h"
#include "AWE/Core/String.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------
/*
namespace Error
{
		ERROR_NOT_SUPPORTED				= AWE_INT32_MIN,	// Map any errors that are not used on
															// a platform to this value
		Success							= 0x00,
		WOULDBLOCK						= WSAEWOULDBLOCK,
		ALREADY							= WSAEALREADY,
		INPROGRESS						= WSAEINPROGRESS,
		ADDRINUSE						= WSAEADDRINUSE,
		ADDRNOTAVAIL					= WSAEADDRNOTAVAIL,
		DESTADDRREQ						= WSAEDESTADDRREQ,
		CONNREFUSED						= WSAECONNREFUSED,
		CONNABORTED						= WSAECONNABORTED,
		CONNRESET						= WSAECONNRESET,
		HOSTDOWN						= WSAEHOSTDOWN,
		HOSTUNREACH						= WSAEHOSTUNREACH,
		ISCONN							= WSAEISCONN,
		NOTCONN							= WSAENOTCONN,
		TIMEDOUT						= WSAETIMEDOUT,
		PROTO							= WSAEPROTOTYPE,
		PERM							= -0x0E,
		NOSR							= -0x0F,
		NOPROTOOPT						= WSAENOPROTOOPT,
		SOCKTNOSUPPORT					= WSAESOCKTNOSUPPORT,
		PROTONOSUPPORT					= WSAEPROTONOSUPPORT,
		OPNOTSUPP						= WSAEOPNOTSUPP,
		AFNOSUPPORT						= WSAEAFNOSUPPORT,
		PFNOSUPPORT						= WSAEPFNOSUPPORT,
		RESTARTSYS						= -0x,
		NETUNREACH						= WSAENETUNREACH,
		NETDOWN							= WSAENETDOWN,
		NETRESET						= WSAENETRESET,
		ACCES							= WSAEACCES,
		LOOP							= WSAELOOP,
		NAMETOOLONG						= WSAENAMETOOLONG,
		NOENT							= -0x18,
		NOTDIR							= -0x1B,
		NOTEMPTY						= WSAENOTEMPTY,
		ROFS							= -0x1C,
		EMFILE							= WSAEMFILE,
		ENFILE							= -0x08,
		NOBUFS							= WSAENOBUFS,
		NOMEM							= WSA_NOT_ENOUGH_MEMORY,
		MSGSIZE							= WSAEMSGSIZE,
		PIPE							= -0x25,
		IO								= -0x26,
		FAULT							= WSAEFAULT,
		INTR							= WSAEINTR,
		BADF							= WSAEBADF,
		INVAL							= WSAEINVAL,
		NOTSOCK							= WSAENOTSOCK,
};

namespace WindowsErrors
{
		SHUTDOWN						= WSAESHUTDOWN,
		TOOMANYREFS						= WSAETOOMANYREFS,
		PROCLIM							= WSAEPROCLIM,
		USERS							= WSAEUSERS,
		DQUOT							= WSAEDQUOT,
		INVALID_HANDLE					= WSA_INVALID_HANDLE,
		STALE							= WSAESTALE,
		REMOTE							= WSAEREMOTE,
		SYSNOTREADY						= WSASYSNOTREADY,
		VERNOTSUPPORTED					= WSAVERNOTSUPPORTED,
		NOTINITIALISED					= WSANOTINITIALISED,
		DISCON							= WSAEDISCON,
		NOMORE							= WSAENOMORE,
		CANCELLED						= WSAECANCELLED,
		INVALIDPROCTABLE				= WSAEINVALIDPROCTABLE,
		INVALIDPROVIDER					= WSAEINVALIDPROVIDER,
		PROVIDEDFAILEDINIT				= WSAEPROVIDERFAILEDINIT,
		SYSCALLFAILURE					= WSASYSCALLFAILURE,
		SERVICE_NOT_FOUND				= WSASERVICE_NOT_FOUND,
		TYPE_NOT_FOUND					= WSATYPE_NOT_FOUND,
		NO_MORE							= WSA_E_NO_MORE,
		CANCELLED						= WSA_E_CANCELLED,
		REFUSED							= WSAEREFUSED,
		HOST_NOT_FOUND					= WSAHOST_NOT_FOUND,
		TRY_AGAIN						= WSATRY_AGAIN,
		NO_RECOVERY						= WSANO_RECOVERY,
		NO_DATA							= WSANO_DATA,
		QOS_RECEIVERS					= WSA_QOS_RECEIVERS,
		QOS_SENDERS						= WSA_QOS_SENDERS,
		INVALID_PARAMETER				= WSA_INVALID_PARAMETER,		// EINVAL?!
		OPERATION_ABORTED				= WSA_OPERATION_ABORTED,
		IO_INCOMPLETE					= WSA_IO_INCOMPLETE,
		IO_PENDING						= WSA_IO_PENDING,
};
*/


namespace Error
{
	enum _t
	{
		// Success == 0
		Success						= 0x0,

		// All errors are < 0
		WouldBlock					= -0x01,
		TryAgain					= -0x02,
		Timeout						= -0x03,
		HostNotFound				= -0x04,
		ConnectionClosed			= -0x05,
		ConnectionRefused			= -0x06,
		InvalidAddress				= -0x07,
		AddressInUse				= -0x08,
		NetworkDown					= -0x09,
		MessageTooBig				= -0x0A,
		InvalidSocket				= -0x0B,
		InvalidOperation			= -0x0C,
		InsufficientResources		= -0x0D,
		InsufficientPrevileges		= -0x0E,
		NotSupported				= -0x0F,
		OperationCancelled			= -0x10,
		OperationInProgress			= -0x11,

		Unknown						= AWE_INT32_MIN,
	};

// ---------------------------------------------------------------

	AWE::Socket::Error::_t		convertNativeError( int iError );
	void			getErrorString( int iError, AWE::Core::String& sString );
	int				getLastNativeError();
	//void			retrieveErrorDetails( int iError, SocketError& kError );
	//void			retrieveErrorDetails( SocketError& kError );

// ---------------------------------------------------------------

};

// ---------------------------------------------------------------
/*
class SocketError
{
	friend void		retrieveErrorDetails( int iError, SocketError& kError );
	friend void		retrieveErrorDetails( SocketError& kError );

	public:
		SocketError();
		~SocketError();

		void			reset();

		int 			getNativeError() const;
		Error::_t		getError() const;
		AWE::Core::String const&	getErrorString() const;

	private:
		void			setNativeError( int iError );
		void			setError( AWE::Socket::Error::_t eError );
		void			setErrorString( AWE::Core::String const& sError );

		int				m_iError;
		AWE::Socket::Error::_t	m_eError;
		AWE::Core::String	m_sError;
};
*/

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
