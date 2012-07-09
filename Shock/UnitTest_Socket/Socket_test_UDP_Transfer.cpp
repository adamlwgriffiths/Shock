#include <cppunit/config/SourcePrefix.h>
#include "Socket_test.h"

// Core Includes
#include "AWE/Core/Core.h"
#include "AWE/Core/SystemPRNG.h"

// Socket Includes
#include "AWE/Socket/Address.h"
#include "AWE/Socket/Socket.h"
#include "AWE/Socket/UDP.h"
#include "AWE/Socket/DatagramProtocolHost.h"
#include "AWE/Socket/DatagramProtocolClient.h"

// System Includes
#include <string.h> /* needed for memset on *nix */

// ---------------------------------------------------------------

namespace {

AWE::Core::String	g_sText( "Hello world!" );
AWE::uint16			g_iServerPort		= 0;
AWE::uint16			g_iClientPort		= 0;
};

// ---------------------------------------------------------------

AWE::uint32 UDP_Transfer_ServerThread::runThread()
{
	AWE::Socket::UDP::Protocol* pUDP = AWE::Socket::UDP::create();
	CPPUNIT_ASSERT( pUDP );

	// listen on our port
	AWE::Socket::Address kLocalAddress;
	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			pUDP->resolveLocalAddress(
				&kLocalAddress,
				0/*SocketTestCase::s_iServPort*/,
				(SocketTestCase::s_bTestIP4 ? AF_INET : AF_INET6)
				)
			) == AWE::Socket::Error::Success
		);

	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			pUDP->createSocket( kLocalAddress.getAddressFamily() )
			) == AWE::Socket::Error::Success
		);

	AWE::Socket::DatagramProtocolHost< AWE::Socket::UDP::Protocol > kHost( pUDP );
	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			kHost.bind( kLocalAddress )
			) == AWE::Socket::Error::Success
		);
	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			pUDP->getBoundAddress( &kLocalAddress )
			) == AWE::Socket::Error::Success
		);

	AWE::Core::String sAddress;
	AWE::uint16 iPort( 0 );
	kLocalAddress.getAddress( &sAddress );
	kLocalAddress.getPort( &g_iServerPort );
	iPort = g_iServerPort;

	std::cout	<< "[Server] Listening for data on IP \"" << sAddress << "\""
				<< " port " << g_iServerPort
				<< std::endl << std::flush;

	SocketTestCase::s_kSemaphore.release();

	AWE::Socket::Address kRemoteAddress;

	// receive some data
	const AWE::uint32 dataSize( 100 );
	AWE::int8 pData[ dataSize ];
	memset( pData, 0, dataSize );

	int recvSize = pUDP->receiveFrom( &kRemoteAddress, pData, dataSize );

	kRemoteAddress.getAddress( &sAddress );
	kRemoteAddress.getPort( &iPort );

	// check we received the correct text
	CPPUNIT_ASSERT( recvSize == g_sText.length() );
	CPPUNIT_ASSERT( strcmp( g_sText.c_str(), pData ) == 0 );

	std::cout	<< "[Server] Received \"" << pData << "\""
				<< " from IP \"" << sAddress << "\""
				<< " port " << iPort
				<< std::endl << std::flush;


#if defined( WAIT_BEFORE_DESTROY )
	// release our mutex so the client can run
	// <<-- Unlock
	SocketTestCase::s_kSemaphore.release();
#endif

	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			pUDP->closeSocket()
			) == AWE::Socket::Error::Success
		);

	AWE_SAFE_DELETE( pUDP );

	return 0;
}

// ---------------------------------------------------------------

AWE::uint32 UDP_Transfer_ClientThread::runThread()
{
	// -->> Lock
	SocketTestCase::s_kSemaphore.aquire();

	AWE::Socket::UDP::Protocol* pUDP = AWE::Socket::UDP::create();
	CPPUNIT_ASSERT( pUDP );

	// listen on our port
	AWE::Socket::Address kRemoteAddress;
	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			pUDP->resolveAddress(
				&kRemoteAddress,
				(SocketTestCase::s_bTestIP4 ? SocketTestCase::s_iServIP_v4 : SocketTestCase::s_iServIP_v6),
				g_iServerPort//,
//				(SocketTestCase::s_bTestIP4 ? AF_INET : AF_INET6)
				)
			) == AWE::Socket::Error::Success
		);

	// don't attempt to bind UDP to port 0
	// http://msdn.microsoft.com/en-us/library/ms737550(VS.85).aspx
// 	AWE::Socket::Address kLocalAddress;
// 	CPPUNIT_ASSERT(
// 		pUDP->resolveLocalAddress(
// 			&kLocalAddress,
// 			0,
// 			kRemoteAddress.getAddressFamily()
// 			) == AWE::Socket::Error::Success
// 		);

	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			pUDP->createSocket( kRemoteAddress.getAddressFamily() )
			) == AWE::Socket::Error::Success
		);

	// Bind
//	AWE::Socket::DatagramProtocolHost< AWE::Socket::UDP::Protocol > kHost( pUDP );
//	CPPUNIT_ASSERT(
//		AWE::Socket::Error::convertNativeError(
//			kHost.bind( kLocalAddress )
//			) == AWE::Socket::Error::Success
//		);

	// Connect
	AWE::Core::String sAddress;
	AWE::uint16 iPort( 0 );

	kRemoteAddress.getAddress( &sAddress );
	kRemoteAddress.getPort( &iPort );

	std::cout	<< "[Client] Sending data to \"" << sAddress << "\""
				<< " port " << iPort
				<< std::endl << std::flush;

	// transfer some text
	AWE::uint32 sendSize( 0 );

	// send isn't guaranteed to send the entire buffer
	// so we must loop
	while ( sendSize != g_sText.length() )
	{
		int iResult = pUDP->sendTo(
			kRemoteAddress,
			g_sText.c_str() + sendSize,
			(AWE::uint32)g_sText.length() - sendSize
			);
		if ( iResult > 0 )
		{
			sendSize += iResult;
		}
	}

	std::cout	<< "[Client] Sent \"" << g_sText << "\"" << std::endl << std::flush;

	CPPUNIT_ASSERT( sendSize == g_sText.length() );

#if defined( WAIT_BEFORE_DESTROY )
	// -->> Lock
	SocketTestCase::s_kSemaphore.aquire();
#endif

	pUDP->closeSocket();

	AWE_SAFE_DELETE( pUDP );

	return 0;
}

// ---------------------------------------------------------------

void SocketTestCase::Socket_IPv4_UDP_Transfer()
{
	// init sockets
	AWE::Socket::init();

	s_bTestIP4 = true;

	AWE::Core::SystemPRNG random;
	random.seed( AWE::Core::Platform::getMilliSecondsSinceSystemStart() );

	for ( AWE::uint32 i = 0; i < 10; i++ )
	{
		// threads
		UDP_Transfer_ServerThread kServerThread;
		UDP_Transfer_ClientThread kClientThread;

		kServerThread.startThread();
		kClientThread.startThread();

		CPPUNIT_ASSERT( kServerThread.joinThread() == 0 );
		CPPUNIT_ASSERT( kClientThread.joinThread() == 0 );
	}

	// shutdown sockets
	AWE::Socket::shutdown();
}

// ---------------------------------------------------------------

void SocketTestCase::Socket_IPv6_UDP_Transfer()
{
	// init sockets
	AWE::Socket::init();

	s_bTestIP4 = false;

	AWE::Core::SystemPRNG random;
	random.seed( AWE::Core::Platform::getMilliSecondsSinceSystemStart() );

	for ( AWE::uint32 i = 0; i < 10; i++ )
	{
		// threads
		UDP_Transfer_ServerThread kServerThread;
		UDP_Transfer_ClientThread kClientThread;

		kServerThread.startThread();
		kClientThread.startThread();

		CPPUNIT_ASSERT( kServerThread.joinThread() == 0 );
		CPPUNIT_ASSERT( kClientThread.joinThread() == 0 );
	}

	// shutdown sockets
	AWE::Socket::shutdown();
}

// ---------------------------------------------------------------
