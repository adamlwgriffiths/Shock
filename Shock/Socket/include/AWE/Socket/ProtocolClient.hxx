
// ---------------------------------------------------------------
// Socket Includes
#include "AWE/Socket/Address.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

AWE_TEMPLATE_EXPORT template < class T >
ProtocolClient< T >::ProtocolClient( T* pProtocol ) :
	m_pProtocol( pProtocol )
{
	AWE_CHECK_PTR( pProtocol );
};

// ---------------------------------------------------------------

AWE_TEMPLATE_EXPORT template < class T >
ProtocolClient< T >::~ProtocolClient()
{
	m_pProtocol = 0;
};

// ---------------------------------------------------------------

AWE_TEMPLATE_EXPORT template < class T >
int ProtocolClient< T >::connect(
	Address const& kAddress
	)
{
	// This should be ok to be set to 0, as an invalid address
	// will cause an exception
	int iResult( 0 );

	if ( kAddress.isValid() == false )
	{
		AWE_THROW( ProtocolClientException, "Address not resolved" );
	}

	AWE_ASSERT( kAddress.isValid() );

	addrinfo* pCurrAddr = kAddress.getAddressInfo();

	while ( pCurrAddr )
	{
		// Bind to the local address
		iResult = ::connect(
			m_pProtocol->getSocket()->getSocket(),
			pCurrAddr->ai_addr,
			(int)pCurrAddr->ai_addrlen
			);

		// check for success
		// the result is either 0 or -1
		// http://msdn.microsoft.com/en-us/library/ms737625(VS.85).aspx
		if ( iResult == 0 )
		{
			break;
		}
		else
		{
			// get the actual error
			iResult = AWE::Socket::Error::getLastNativeError();
		}

		pCurrAddr = pCurrAddr->ai_next;
	}

	return iResult;
};

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
