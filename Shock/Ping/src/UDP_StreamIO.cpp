#include "AWE/Network/UDP_StreamIO.h"
// ---------------------------------------------------------------

// Net Includes
#include "AWE/Socket/UDP_Socket.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Network {

// ---------------------------------------------------------------

UDP_StreamIO::UDP_StreamIO() :
	StreamIO(),
	m_pSocket(0),
	m_kRecvAddress(""),
	m_kRecvPort(0)
{
	m_pSocket = AWE::Socket::UDP_Socket::create();
}

// ---------------------------------------------------------------

UDP_StreamIO::~UDP_StreamIO()
{
	AWE_SAFE_DELETE( m_pSocket );
}

// ---------------------------------------------------------------

AWE::uint32 UDP_StreamIO::read( AWE::int8* pData, AWE::uint32 iMaxLength )
{
	// listen for data and store the address in our member variables
return 0;//	return m_pSocket->receive( pData, iMaxLength, m_kRecvAddress, m_kRecvPort );
}

// ---------------------------------------------------------------

AWE::uint32 UDP_StreamIO::write( AWE::int8* pData, AWE::uint32 iLength )
{
	AWE::uint32 sentSize(0);

	// send all the data
	while ( sentSize != iLength )
	{
//		sentSize += m_pSocket->send( pData, iLength );
	}

	return sentSize;
}

// ---------------------------------------------------------------

void UDP_StreamIO::init()
{
	m_pSocket->init();
}

// ---------------------------------------------------------------

void UDP_StreamIO::shutdown()
{
	m_pSocket->shutdown();
}

// ---------------------------------------------------------------

void UDP_StreamIO::setBlocking( bool bBlocking )
{
	m_pSocket->setBlocking( bBlocking );
}

// ---------------------------------------------------------------

void UDP_StreamIO::setOption( AWE::Socket::Socket::Option eOption, AWE::uint32 iValue )
{
return;//	m_pSocket->setOption( eOption, iValue );
}

// ---------------------------------------------------------------

bool UDP_StreamIO::connect( AWE::Core::String const& sAddress, AWE::uint16 iPort )
{
return false;//	return m_pSocket->connect( sAddress, iPort );
}

// ---------------------------------------------------------------

bool UDP_StreamIO::bind( AWE::uint16 iPort, AWE::Core::String const& sInterfaceIP )
{
return false;//	return m_pSocket->bind( iPort, sInterfaceIP );
}

// ---------------------------------------------------------------

void UDP_StreamIO::getSendersDetails( AWE::Core::String& sAddress, AWE::uint16& iPort )
{
	// check we've actually received something
	if ( (sAddress.length() == 0)  &&  (iPort == 0) )
	{
		AWE_THROW( StreamIO_Exception, "Attempted to retrieve details for last sender when none exists" );
	}

	sAddress = m_kRecvAddress;
	iPort = m_kRecvPort;
}

// ---------------------------------------------------------------

}; // namespace Network
}; // namespace AWE

// ---------------------------------------------------------------
