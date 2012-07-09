#include "AWE/Ping/Ping.h"
// ---------------------------------------------------------------

// Core Includes
#include "AWE/Core/Core.h"
#include "AWE/Core/Thread.h"
#include "AWE/Core/TimeConversion.h"

// Socket Includes
#include "AWE/Socket/DatagramProtocolHost.h"
#include "AWE/Socket/ICMP.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Ping {

// ---------------------------------------------------------------

namespace {
	const AWE::uint32 DEFAULT_TIMEOUT_MS	= 1000;
	const AWE::uint32 MAX_DATA_SIZE			= 1024;
	const AWE::uint32 DEFAULT_TTL			= 255;
	const AWE::uint32 PING_PORT				= 53;

	const AWE::uint32 ICMP_ECHO				= 8;
	const AWE::uint32 ICMP_ECHOREPLY		= 0;
	const AWE::uint32 ICMP_MIN				= 8;			// Minimum 8 byte ICMP packet
};

// ---------------------------------------------------------------

Ping::Ping( AWE::Core::String const& sAddress ) :
	m_pICMP(0),
	m_iPacketSize(0),
	m_iDataSize(0),
	m_pICMP_Data(0),
	m_pReceiveBuffer(0),
	m_iReceiveBufferSize(0),
	m_sAddress( sAddress ),
	m_kAddress(),
	m_iRecvTimeout( DEFAULT_TIMEOUT_MS ),
	m_pTimer( 0 )
{
}

// ---------------------------------------------------------------

Ping::~Ping()
{
	AWE_ASSERT( m_pICMP == 0 );
	AWE_ASSERT( m_pReceiveBuffer == 0 );
	AWE_ASSERT( m_pICMP_Data == 0 );
	AWE_ASSERT( m_pTimer == 0 );
}

// ---------------------------------------------------------------

int Ping::init(
	AWE::uint32 iTimeoutMilliseconds,
	AWE::uint32 iDataLength
	)
{
	m_iDataSize = iDataLength;
	m_iReceiveBufferSize = sizeof(struct PingICMP_Header) + MAX_DATA_SIZE;
	m_pReceiveBuffer = new AWE::int8[ m_iReceiveBufferSize ];
	memset( m_pReceiveBuffer, 0, m_iReceiveBufferSize );

	// setup the socket

	// we need a raw ICMP socket so we can inspect IP headers
	m_pICMP = AWE::Socket::ICMP::create();

	// we want to work with a raw socket
	// we must set this before we create the socket
	m_pICMP->setRawSocket( true );

	// resolve the target address
	int iResult = m_pICMP->resolveAddress( &m_kAddress, m_sAddress, PING_PORT );
	if ( iResult != 0 )
	{
		// cleanup
		AWE_SAFE_DELETE( m_pICMP );
		AWE_SAFE_DELETE_ARRAY( m_pReceiveBuffer );
		return iResult;
	}

	// create a socket in the same address family
	iResult = m_pICMP->createSocket( m_kAddress.getAddressFamily() );

	if ( iResult != 0 )
	{
		// cleanup
		shutdown();
		return iResult;
	}

	setTimeout( iTimeoutMilliseconds );

	// we cannot bind our ICMP socket or it
	// will silently fail on XP SP2 and Vista
	// http://msdn.microsoft.com/en-us/library/ms740548.aspx

	// setup our ping packet

	setupPacket();

	// create our timer
	m_pTimer = AWE::Core::HighPerformanceTimer::createHighPerformanceTimer();

	return 0;
}

// ---------------------------------------------------------------

void Ping::shutdown()
{
	// ICMP Protocol
	if ( m_pICMP )
	{
		if ( m_pICMP->isValidSocket() )
		{
			m_pICMP->closeSocket();
		}
		AWE_SAFE_DELETE( m_pICMP );
	}

	// Buffers
	AWE_SAFE_DELETE_ARRAY( m_pReceiveBuffer );
	AWE_SAFE_DELETE_ARRAY( m_pICMP_Data );

	// Timer
	AWE_SAFE_DELETE( m_pTimer );
}

// ---------------------------------------------------------------

void Ping::setTimeout( AWE::uint32 iTimeoutMilliSeconds )
{
	m_iRecvTimeout = iTimeoutMilliSeconds;
}

// ---------------------------------------------------------------

AWE::Core::String const& Ping::getTargetAddress() const
{
	return m_sAddress;
}

// ---------------------------------------------------------------

void Ping::setupPacket()
{
	if ( m_iDataSize > MAX_DATA_SIZE )
	{
		m_iDataSize = MAX_DATA_SIZE;
	}

	size_t iHeaderSize( sizeof(PingICMP_Header) );
	m_iPacketSize = m_iDataSize + iHeaderSize;

	m_pICMP_Data = new AWE::int8[ m_iPacketSize ];
	memset( m_pICMP_Data, 0, m_iPacketSize );

	struct PingICMP_Header* pICMP_Header = (struct PingICMP_Header*)m_pICMP_Data;  

	// setup ICMP header
	pICMP_Header->type		= ICMP_ECHO;
	pICMP_Header->code		= 0;
	pICMP_Header->seq		= 0;

	// fill in data
	AWE::int8* pDatapart = m_pICMP_Data + iHeaderSize;
	size_t iDataSize = m_iPacketSize - iHeaderSize;
	AWE_ASSERT( iDataSize == m_iDataSize );

	// we'll do the same as windows which pings
	// with a repeating sequence of letters from a-w
	char cCurrChar = 'a';
	for ( size_t i = 0; i < m_iDataSize; i++ )
	{
		pDatapart[ i ] = cCurrChar;
		cCurrChar++;
		if ( cCurrChar > 'w' )
		{
			cCurrChar = 'a';
		}
	}
	//memset( pDatapart, 'E', iDataSize ); 
}

// ---------------------------------------------------------------

void Ping::updatePacket()
{
	struct PingICMP_Header* pICMP_Header = (struct PingICMP_Header*)m_pICMP_Data;  

	// http://www.rhyshaden.com/icmp.htm
	// setup ICMP header
	pICMP_Header->id		= ( (AWE::uint16)AWE::Core::Thread::currentThreadID() & 0xFFFF );
	pICMP_Header->timestamp = ( AWE::Core::Platform::getMilliSecondsSinceSystemStart() & 0xFFFFFFFF ); 
	pICMP_Header->seq++;

	pICMP_Header->checksum = 0; // zero our checksum before we set a new one

	// update the checksum
	pICMP_Header->checksum = checksum(
		(AWE::uint16*) m_pICMP_Data,
		m_iPacketSize		// checksum takes the number of uint8s, not int16s
		);
}

// ---------------------------------------------------------------

AWE::uint16 Ping::checksum( AWE::uint16* pBuffer, AWE::uint32 iUint8_Size )
{
	AWE::uint32 iChecksum( 0 );
	AWE::uint32 iIndex( 0 );

	for (
		AWE::uint32 iIndex = iUint8_Size;
		iIndex > 1;
		iIndex -= sizeof(AWE::int16)
		)
	{
		iChecksum += *pBuffer++;
	}

	if ( iIndex > 0 )
	{
		iChecksum += *(AWE::int8*)pBuffer;
	}

	iChecksum = (iChecksum >> 16) + (iChecksum & 0xffff);
	iChecksum += (iChecksum >> 16);

	return (AWE::uint16)( ~iChecksum );
}

// ---------------------------------------------------------------

int Ping::ping()
{
	AWE_CHECK_PTR( m_pTimer );
	AWE_CHECK_PTR( m_pICMP );
	AWE_CHECK_PTR( m_pICMP_Data );

 	// update our packet
	// we have to do this here to get the thread ID correct
	updatePacket();

	// we're going to send a packet
	m_kStats.incrementTransmitted();

	// send out the ping
	m_pTimer->start();

	int iResult = sendPing();
	if ( iResult != 0 )
	{
		return iResult;
	}

	// listen for a ping
	iResult = receivePing();

	AWE::float64 fSeconds( m_pTimer->stop() );

	if ( iResult != 0 )
	{
		return iResult;
	}

	// work out the round trip time
	AWE::float64 fRTT( 0.0f );
	AWE::Core::TimeConversion::secondsToMilli( fSeconds, fRTT );
	AWE::uint32 iRTT = (AWE::uint32)fRTT;
	m_kStats.incrementReceived( iRTT );

	return iResult;
}

// ---------------------------------------------------------------

int Ping::sendPing()
{
	// send the ping out our socket
	AWE::int32 iSentSize = 0;
	do 
	{
		AWE::int32 iSent( m_pICMP->sendTo( m_kAddress, m_pICMP_Data, m_iPacketSize ) );

		// error
		if ( iSent < 0 )
		{
			return iSent;
		}

		iSentSize += iSent;
	} while( iSentSize != m_iPacketSize );

	return 0;
}

// ---------------------------------------------------------------

int Ping::receivePing()
{
	//
	// listen for a ping back
	//

	memset( m_pReceiveBuffer, 0, m_iReceiveBufferSize );
	bool bKeepLooping(true);


	AWE::float64 fStartTime( m_pTimer->getTime() );
	AWE::float64 fAccumTime( 0.0 );

	do 
	{
		// update our accumulated time
		fAccumTime += ( m_pTimer->getTime() - fStartTime );

		// HACK: we should really be setting up a select here
		// but non blocking sockets are a pain
		// convert to milliseconds
		AWE::float64 fAccumMS( 0.0f );
		AWE::Core::TimeConversion::secondsToMilli( fAccumTime, fAccumMS );
		AWE::uint32 iAccumMS = (AWE::uint32)fAccumMS;
		AWE::int32 iTimeLeft( (AWE::int32)m_iRecvTimeout - (AWE::int32)iAccumMS );
		AWE::int32 iRecvSize = m_pICMP->getSocket()->setReceiveTimeout( iTimeLeft );

		if ( iRecvSize < 0 )
		{
			return iRecvSize;
		}

		AWE::Socket::Address kRecvAddress;
		iRecvSize = m_pICMP->receiveFrom(
			&kRecvAddress,
			m_pReceiveBuffer,
			m_iReceiveBufferSize
			);

		// check for errors
		if ( iRecvSize < 0 )
		{
			// the error is already in our own format
			return iRecvSize;
		}

		if ( parsePacket( iRecvSize ) )
		{
			// we've received a ping
			bKeepLooping = false;
		}
	} while( bKeepLooping );

	return 0;
}

// ---------------------------------------------------------------

bool Ping::parsePacket( AWE::int32 iRecvSize )
{
	//
	// de-construct our received message
	//

	struct PingICMP_Header* pICMP_Header = 0;
	AWE::uint32 iIP_HeaderLength;
	AWE::uint32 iRTT;

	if ( m_pICMP->getProtocol() == IPPROTO_ICMP )
	{
		struct AWE::Network::IPv4_Header* pIP_Header = 0;

		pIP_Header = (struct AWE::Network::IPv4_Header*)m_pReceiveBuffer;
		iIP_HeaderLength = pIP_Header->h_len * 4 ; // number of 32-bit words *4 = bytes

		//
		// validate
		//

		// packet size
		if ( (AWE::uint32)iRecvSize < iIP_HeaderLength + ICMP_MIN )
		{
			return false;
		}

		pICMP_Header = (struct PingICMP_Header*)(m_pReceiveBuffer + iIP_HeaderLength);
	}
	else if ( m_pICMP->getProtocol() == IPPROTO_ICMPV6 )
	{
		// ICMPv6 not supported
		return false;
	}
	else
	{
		// Unknown protocol
		return false;
	}

	// check the message type
	if (pICMP_Header->type != ICMP_ECHOREPLY)
	{
		return false;
	}

	// check the ping id
	if ( pICMP_Header->id != AWE::Core::Thread::currentThreadID() )
	{
		return false;
	}

	// ensure this is the current ping reply
	if ( pICMP_Header->seq != m_kStats.getNumberTransmitted() )
	{
		return false;
	}

	//
	// extract data
	//

	// round trip time = current time - start time
	iRTT = AWE::Core::Platform::getMilliSecondsSinceSystemStart() - pICMP_Header->timestamp;

	// update our statistics
	m_kStats.incrementReceived( iRTT );

	return true;
}

// ---------------------------------------------------------------

AWE::Ping::Ping::Statistics const& Ping::getStatistics() const
{
	return m_kStats;
}

// ---------------------------------------------------------------

Ping::Statistics::Statistics() :
	m_iRTT(0),
	m_iMinRTT(-1),
	m_iMaxRTT(0),
	m_iAccumulatedRTT(0),
	m_iTransmitted(0),
	m_iReceived(0),
	m_bReceivedLast(false)
{
}

// ---------------------------------------------------------------

Ping::Statistics::~Statistics()
{

}

// ---------------------------------------------------------------

void Ping::Statistics::reset()
{
	m_iRTT = 0;
	m_iMinRTT = -1;
	m_iMaxRTT = 0;
	m_iAccumulatedRTT = 0;
	m_iTransmitted = 0;
	m_iReceived = 0;
	m_bReceivedLast = false;
}

// ---------------------------------------------------------------

void Ping::Statistics::incrementTransmitted()
{
	m_iTransmitted++;

	// clear the current RTT
	m_iRTT = 0;
	m_bReceivedLast = false;
}

// ---------------------------------------------------------------

void Ping::Statistics::incrementReceived( AWE::uint32 iRoundTripTime )
{
	m_iRTT = iRoundTripTime;
	m_iAccumulatedRTT += iRoundTripTime;
	m_iReceived++;
	m_bReceivedLast = true;

	if ( iRoundTripTime > m_iMaxRTT )
	{
		m_iMaxRTT = iRoundTripTime;
	}
	if ( iRoundTripTime < m_iMinRTT )
	{
		m_iMinRTT = iRoundTripTime;
	}
}

// ---------------------------------------------------------------

AWE::uint32 Ping::Statistics::getRoundTripTime() const
{
	return m_iRTT;
}

// ---------------------------------------------------------------

AWE::uint32 Ping::Statistics::getMinimumRoundTripTime() const
{
	return m_iMinRTT;
}

// ---------------------------------------------------------------

AWE::uint32 Ping::Statistics::getMaximumRoundTripTime() const
{
	return m_iMaxRTT;
}

// ---------------------------------------------------------------

AWE::uint32 Ping::Statistics::getAccumulatedRoundTripTime() const
{
	return m_iAccumulatedRTT;
}

// ---------------------------------------------------------------

AWE::uint32 Ping::Statistics::getNumberTransmitted() const
{
	return m_iTransmitted;
}

// ---------------------------------------------------------------

AWE::uint32 Ping::Statistics::getNumberReceived() const
{
	return m_iReceived;
}

// ---------------------------------------------------------------

bool Ping::Statistics::receivedLast() const
{
	return m_bReceivedLast;
}

// ---------------------------------------------------------------

}; // namespace Ping
}; // namespace AWE

// ---------------------------------------------------------------
