#include "AWE/Socket/Socket.h"
// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

void retrieveErrorDetails( int iError, SocketError& kError )
{
	AWE::Core::String sError;

	// convert to more usable format
	Error::_t eError = convertNativeError( iError );

	// get a description of the error
	getErrorString( iError, sError );

	kError.setNativeError( iError );
	kError.setError( eError );
	kError.setErrorString( sError );
}

// ---------------------------------------------------------------

void retrieveErrorDetails( SocketError& kError )
{
	AWE::Core::String sError;
	int iError = getLastNativeError();

	// convert to more usable format
	Error::_t eError = convertNativeError( iError );

	// get a description of the error
	getErrorString( iError, sError );

	kError.setNativeError( iError );
	kError.setError( eError );
	kError.setErrorString( sError );
}

// ---------------------------------------------------------------

SocketError::SocketError() :
	m_iError( 0 ),
	m_eError( AWE::Socket::Error::Error_Success ),
	m_sError()
{
}

// ---------------------------------------------------------------

SocketError::~SocketError()
{
}

// ---------------------------------------------------------------

void SocketError::reset()
{
	m_iError = 0;
	m_eError = AWE::Socket::Error::Error_Success;
	m_sError = AWE::Core::String();
}

// ---------------------------------------------------------------

int SocketError::getNativeError() const
{
	return m_iError;
}

// ---------------------------------------------------------------

AWE::Socket::Error::_t SocketError::getError() const
{
	return m_eError;
}

// ---------------------------------------------------------------

AWE::Core::String const& SocketError::getErrorString() const
{
	return m_sError;
}

// ---------------------------------------------------------------

void SocketError::setNativeError( int iError )
{
	m_iError = iError;
}

// ---------------------------------------------------------------

void SocketError::setError( AWE::Socket::Error::_t eError )
{
	m_eError = eError;
}

// ---------------------------------------------------------------

void SocketError::setErrorString( AWE::Core::String const& sError )
{
	m_sError = sError;
}

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
