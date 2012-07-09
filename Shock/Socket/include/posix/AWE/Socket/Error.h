#pragma once

// ---------------------------------------------------------------
// Core Includes
#include "AWE/Core/String.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

typedef int			NativeError;

// ---------------------------------------------------------------

namespace Error
{
	enum _t
	{
/*
		Success							=  0x00,
		WOULDBLOCK						= -0x01,
		ALREADY							= -0x,
		INPROGRESS						= -0x,
		ADDRINUSE						= -0x14,
		ADDRNOTAVAIL					= -0x15,
		DESTADDRREQ						= -0x1A,
		CONNREFUSED						= -0x,
		CONNABORTED						= -0x04,
		CONNRESET						= -0x,
		HOSTDOWN						= -0x,
		HOSTUNREACH						= -0x,
		ISCONN							= -0x,
		NOTCONN							= -0x19,
		TIMEDOUT						= -0x23,
		PROTO							= -0x0D,
		PERM							= -0x0E,
		NOSR							= -0x0F,
		NOPROTOOPT						= -0x,
		SOCKTNOSUPPORT					= -0x,
		PROTONOSUPPORT					= -0x,
		OPNOTSUPP						= -0x,
		AFNOSUPPORT						= -0x,
		PFNOSUPPORT						= -0x,
		RESTARTSYS						= -0x,
		NETUNREACH						= -0x22,
		NETDOWN							= -0x,
		NETRESET						= -0x,
		ACCES							= -0x13,
		LOOP							= -0x16,
		NAMETOOLONG						= -0x17,
		NOENT							= -0x18,
		NOTDIR							= -0x1B,
		ROFS							= -0x1C,
		EMFILE							= -0x07,
		ENFILE							= -0x08,
		NOBUFS							= -0x09,
		NOMEM							= -0x0A,
		MSGSIZE							= -0x24,
		PIPE							= -0x25,
		IO								= -0x26,
		FAULT							= -0x02,
		INTR							= -0x03,
		BADF							= -0x05,
		INVAL							= -0x06,
		NOTSOCK							= -0x0B,
		SHUTDOWN						= -0x,
*/

		// Success == 0
		Error_Success					= 0x0,

		// All errors are < 0
		Error_Failure					= -0x01,
		Error_WouldBlock				= -0x02,
		Error_TryAgain					= -0x03,
		Error_Timeout					= -0x04,
		Error_HostNotFound				= -0x05,
		Error_ConnectionClosed			= -0x06,
		Error_ConnectionRefused			= -0x07,
		Error_InvalidAddress			= -0x08,
		Error_AddressInUse				= -0x09,
		Error_NetworkDown				= -0x0A,
		Error_MessageTooBig				= -0x0B,
		Error_InvalidSocket				= -0x0C,
		Error_InvalidOperation			= -0x0D,
		Error_InsufficientResources		= -0x0E,
		Error_InsufficientPrevileges	= -0x0F,
		Error_NotSupported				= -0x10,
		Error_OperationCancelled		= -0x11,
		Error_OperationInProgress		= -0x12,
	};
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

AWE::Socket::Error::_t		convertNativeError( int iError );
void			getErrorString( int iError, AWE::Core::String& sString );
int				getLastNativeError();
//void			retrieveErrorDetails( int iError, SocketError& kError );
//void			retrieveErrorDetails( SocketError& kError );

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
