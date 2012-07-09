#pragma once

// ---------------------------------------------------------------
// Socket Includes
#include "AWE/Socket/Address.h"
#include "AWE/Socket/DatagramProtocol.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {
namespace ICMP {

// ---------------------------------------------------------------
class Protocol :
	public AWE::Socket::DatagramProtocol
{
	public:
		Protocol( Socket* pSocket );
		virtual ~Protocol();

		int						createSocket( int iAF );

		virtual int				getProtocol() const;

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
		int			m_iProtocol;
};

// ---------------------------------------------------------------

AWE::Socket::ICMP::Protocol*		create();

// ---------------------------------------------------------------

}; // namespace ICMP
}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
