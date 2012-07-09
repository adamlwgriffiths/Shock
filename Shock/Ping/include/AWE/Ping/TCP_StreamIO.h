#pragma once

// ---------------------------------------------------------------
// Project Includes
#include "AWE/IO/StreamIO.h"

// Net Includes
#include "AWE/Socket/TCP_Socket.h"

// ---------------------------------------------------------------
// Pre-Declarations
namespace AWE {
namespace Socket {

class TCP_Socket;

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------

namespace AWE {
namespace Network {

// ---------------------------------------------------------------

class TCP_StreamIO :
	public AWE::IO::StreamIO
{
	public:
		TCP_StreamIO();
		virtual ~TCP_StreamIO();

		virtual AWE::uint32	read( AWE::int8* pData, AWE::uint32 iMaxLength );
		virtual AWE::uint32	write( AWE::int8* pData, AWE::uint32 iLength );

		virtual void		init();
		virtual void		shutdown();

		virtual void		setBlocking( bool bBlocking );
		virtual void		setOption( AWE::Socket::Socket::Option eOption, AWE::uint32 iValue );

		virtual bool		bind( AWE::uint16 iPort, AWE::Core::String const& sInterfaceIP = "" );
		virtual bool		connect( AWE::Core::String const& sAddress, AWE::uint16 iPort );
		virtual bool		listen( AWE::uint32 iMaxPendingConnections );
		virtual AWE::int32	accept( AWE::Socket::StreamSocket** pSocket );

	protected:
		AWE::Socket::TCP_Socket*		m_pSocket;
};

// ---------------------------------------------------------------

}; // namespace Network
}; // namespace AWE

// ---------------------------------------------------------------
