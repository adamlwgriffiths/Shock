#include "AWE/Network/TCP_StreamIO.h"
// ---------------------------------------------------------------

// Net Includes
#include "AWE/Socket/TCP_Socket.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Network {

// ---------------------------------------------------------------

TCP_StreamIO::TCP_StreamIO() :
	StreamIO(),
	m_pSocket(0)
{
	m_pSocket = AWE::Socket::TCP_Socket::create();
}

// ---------------------------------------------------------------

TCP_StreamIO::~TCP_StreamIO()
{
	AWE_SAFE_DELETE( m_pSocket );
}

// ---------------------------------------------------------------

AWE::uint32 TCP_StreamIO::read( AWE::int8* pData, AWE::uint32 iMaxLength )
{
	return m_pSocket->receive( pData, iMaxLength );
}

// ---------------------------------------------------------------

AWE::uint32 TCP_StreamIO::write( AWE::int8* pData, AWE::uint32 iLength )
{
	AWE::uint32 sentSize(0);

	// send all the data
	while ( sentSize != iLength )
	{
		sentSize += m_pSocket->send( pData, iLength );
	}

	return sentSize;
}

// ---------------------------------------------------------------

void TCP_StreamIO::init()
{
	m_pSocket->init();
}

// ---------------------------------------------------------------

void TCP_StreamIO::shutdown()
{
	m_pSocket->shutdown();
}

// ---------------------------------------------------------------

void TCP_StreamIO::setBlocking( bool bBlocking )
{
	m_pSocket->setBlocking( bBlocking );
}

// ---------------------------------------------------------------

void TCP_StreamIO::setOption( AWE::Socket::Socket::Option eOption, AWE::uint32 iValue )
{
	m_pSocket->setOption( eOption, iValue );
}

// ---------------------------------------------------------------

bool TCP_StreamIO::bind( AWE::uint16 iPort, AWE::Core::String const& sInterfaceIP )
{
return false;//	return m_pSocket->bind( iPort, sInterfaceIP );
}

// ---------------------------------------------------------------

bool TCP_StreamIO::connect(
	AWE::Core::String const& sAddress,
	AWE::uint16 iPort
	)
{
return false;//	return m_pSocket->connect( sAddress, iPort );
}

// ---------------------------------------------------------------

bool TCP_StreamIO::listen( AWE::uint32 iMaxPendingConnections )
{
	return m_pSocket->listen( iMaxPendingConnections );
}

// ---------------------------------------------------------------

AWE::int32 TCP_StreamIO::accept( AWE::Socket::StreamSocket** pSocket )
{
	return m_pSocket->accept( pSocket );
}

// ---------------------------------------------------------------

}; // namespace Network
}; // namespace AWE

// ---------------------------------------------------------------
