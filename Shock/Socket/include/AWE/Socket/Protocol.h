#pragma once

// ---------------------------------------------------------------
// Socket Includes
#include "AWE/Socket/Address.h"
#include "AWE/Socket/Socket.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

class Protocol
{
	public:
		// ---------------------------------------------------------------
		// Exceptions
		AWE_DEFINE_EXCEPTION( ProtocolException );

		// ---------------------------------------------------------------

		virtual ~Protocol();

		virtual int				createSocket( int iAF);
		virtual int				closeSocket();

		bool					isValidSocket() const;
		Socket*					getSocket() const;
		virtual int				getProtocol() const = 0;
		virtual int				getSocketType() const = 0;

		virtual int				getBoundAddress(
			AWE::Socket::Address* pAddress
			);

		int						resolveLocalAddress(
			Address* pAddress,
			AWE::uint16 iPort,
			int iAF = AF_UNSPEC
			);
		int						resolveAddress(
			Address* pAddress,
			AWE::Core::String const& sAddress,
			AWE::uint16 iPort
			);

	protected:
		Protocol( Socket* pSocket );

		Socket*			m_pSocket;
};

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
