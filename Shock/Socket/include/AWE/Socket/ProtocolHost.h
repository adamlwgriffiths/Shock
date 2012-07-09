#pragma once

// ---------------------------------------------------------------
// Socket Includes
#include "AWE/Socket/Protocol.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

template < class T >
class ProtocolHost
{
	public:
		// ---------------------------------------------------------------
		// Exceptions
		AWE_DEFINE_EXCEPTION( ProtocolHostException );

		// ---------------------------------------------------------------

		ProtocolHost( T* pProtocol );
		virtual ~ProtocolHost();

		int						bind(
			int iAF,
			AWE::uint16 iPort
			);
		int						bind(
			Address const& kAddress
			);

	protected:
		T*			m_pProtocol;
};

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------

#ifndef AWE_TEMPLATE_EXPORT_KEYWORD
#	include "ProtocolHost.hxx"
#endif

// ---------------------------------------------------------------
