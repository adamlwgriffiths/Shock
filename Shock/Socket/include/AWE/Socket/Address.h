#pragma once

// ---------------------------------------------------------------
// Socket Includes
#include "AWE/Socket/Platform.h"
#include "AWE/Socket/Error.h"

// Core Includes
#include "AWE/Core/String.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

class Address
{
	public:
		// ---------------------------------------------------------------
		// Exceptions

		AWE_DEFINE_EXCEPTION( AddressException );

		// ---------------------------------------------------------------

		Address();
		Address( addrinfo* pAddrInfo );
		~Address();

		int						resolve(
			int iAF,
			int iProtocol,
			int iSockType,
			int iFlags,
			AWE::Core::String const& sAddress = AWE::Core::String(),
			AWE::uint16 iPort = 0
			);

		int						resolve(
			addrinfo* pHints,
			AWE::Core::String const& sAddress = AWE::Core::String(),
			AWE::uint16 iPort = 0
			);

		bool					isValid() const;

		int						getAddressFamily() const;
		addrinfo*				getAddressInfo() const;

		int						getAddress(
			AWE::Core::String* pAddress
			);
		int						getPort(
			AWE::uint16* pPort
			) const;

		int						lookupHostname(
			AWE::Core::String* pHostname
			);

	protected:
		int						reverseLookup(
			int iLookupFlags,
			AWE::Core::String* pHostname,
			AWE::uint16* pPort
			) const;

		addrinfo*			m_pAddrInfo;
};

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
