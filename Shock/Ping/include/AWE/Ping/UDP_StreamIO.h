#pragma once

// ---------------------------------------------------------------
// Project Includes
#include "AWE/IO/StreamIO.h"

// Net Includes
#include "AWE/Socket/Socket.h"

// ---------------------------------------------------------------
// Pre-Declarations
namespace AWE {
namespace Socket {

class UDP_Socket;

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------

namespace AWE {
namespace Network {

// ---------------------------------------------------------------

class UDP_StreamIO :
	public AWE::IO::StreamIO
{
	public:
		UDP_StreamIO();
		virtual ~UDP_StreamIO();

		virtual AWE::uint32	read( AWE::int8* pData, AWE::uint32 iMaxLength );
		virtual AWE::uint32	write( AWE::int8* pData, AWE::uint32 iLength );

		virtual void		init();
		virtual void		shutdown();

		virtual void		setBlocking( bool bBlocking );
		virtual void		setOption( AWE::Socket::Socket::Option eOption, AWE::uint32 iValue );

		virtual bool		bind( AWE::uint16 iPort, AWE::Core::String const& sInterfaceIP = "" );
		virtual bool		connect( AWE::Core::String const& sAddress, AWE::uint16 iPort );

		/*!
		 * \brief Retrieve the address and port of the sender of the last packet.
		 *
		 * As IO Streams have no concept of a sender, this method can be used to
		 * query for the origin of the last received packet.
		 *
		 * \param sAddress	The address of the sender.
		 * \throws UDP_NoPreviousSender	Thrown if no previous sender exists.
		 */
		virtual void		getSendersDetails( AWE::Core::String& sAddress, AWE::uint16& iPort );

	protected:
		AWE::Socket::UDP_Socket*	m_pSocket;

		AWE::Core::String			m_kRecvAddress;
		AWE::uint16					m_kRecvPort;
};

// ---------------------------------------------------------------

}; // namespace Network
}; // namespace AWE

// ---------------------------------------------------------------
