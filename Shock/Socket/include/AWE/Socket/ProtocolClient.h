#pragma once

// ---------------------------------------------------------------
// Socket Includes
#include "AWE/Socket/Address.h"
#include "AWE/Socket/Protocol.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

template < class T >
class ProtocolClient
{
	public:
		// ---------------------------------------------------------------
		// Exceptions
		AWE_DEFINE_EXCEPTION( ProtocolClientException );

		// ---------------------------------------------------------------

		ProtocolClient( T* pProtocol );
		virtual ~ProtocolClient();

		int						connect( Address const& kAddress );

	protected:
		T*			m_pProtocol;
};

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------

#ifndef AWE_TEMPLATE_EXPORT_KEYWORD
#	include "ProtocolClient.hxx"
#endif

// ---------------------------------------------------------------
