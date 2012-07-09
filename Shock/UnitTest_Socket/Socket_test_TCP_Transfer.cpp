#include <cppunit/config/SourcePrefix.h>
#include "Socket_test.h"

// Core Includes
#include "AWE/Core/Core.h"
#include "AWE/Core/SystemPRNG.h"

// Socket Includes
#include "AWE/Socket/Address.h"
#include "AWE/Socket/Socket.h"
#include "AWE/Socket/TCP.h"
#include "AWE/Socket/StreamProtocolHost.h"
#include "AWE/Socket/StreamProtocolClient.h"

// ---------------------------------------------------------------

namespace {

AWE::Core::String	g_sText( "Hello world!" );
AWE::uint16			g_iServerPort		= 0;
AWE::uint16			g_iClientPort		= 0;
};

// ---------------------------------------------------------------

AWE::uint32 TCP_Transfer_ServerThread::runThread()
{
	AWE::Socket::TCP::Protocol* pTCP = AWE::Socket::TCP::create();
	CPPUNIT_ASSERT( pTCP );

	// listen on our port
	AWE::Socket::Address kLocalAddress;
	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			pTCP->resolveLocalAddress(
				&kLocalAddress,
				0/*SocketTestCase::s_iServPort*/,
				(SocketTestCase::s_bTestIP4 ? AF_INET : AF_INET6)
				)
			) == AWE::Socket::Error::Success
		);

	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			pTCP->createSocket( kLocalAddress.getAddressFamily() )
			) == AWE::Socket::Error::Success
		);

	AWE::Socket::StreamProtocolHost< AWE::Socket::TCP::Protocol > kHost( pTCP );
	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			kHost.bind( kLocalAddress )
			) == AWE::Socket::Error::Success
		);
	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			pTCP->getBoundAddress( &kLocalAddress )
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

	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			kHost.listen()
			) == AWE::Socket::Error::Success
		);

	AWE::Socket::Address kRemoteAddress;
	AWE::Socket::TCP::Protocol* pRemoteConn = 0;
	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			kHost.accept( &pRemoteConn, &kRemoteAddress )
			) == AWE::Socket::Error::Success
		);
	CPPUNIT_ASSERT( pRemoteConn );

	kRemoteAddress.getAddress( &sAddress );
	kRemoteAddress.getPort( &iPort );

	std::cout	<< "[Server] Received connection from IP \"" << sAddress << "\""
				<< " port " << iPort
				<< std::endl << std::flush;

	// receive some data
	const AWE::uint32 dataSize( 100 );
	AWE::int8 pData[ dataSize ];
	memset( pData, 0, dataSize );

	AWE::uint32 recvSize( pRemoteConn->receive( pData, dataSize ) );

	// check we received the correct text
	CPPUNIT_ASSERT( recvSize == g_sText.length() );
	CPPUNIT_ASSERT( strcmp( g_sText.c_str(), pData ) == 0 );

	std::cout	<< "[Server] Received \"" << pData << "\""
				<< std::endl << std::flush;


#if defined( WAIT_BEFORE_DESTROY )
	// release our mutex so the client can run
	// <<-- Unlock
	SocketTestCase::s_kSemaphore.release();
#endif

	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			pRemoteConn->closeSocket()
			) == AWE::Socket::Error::Success
		);
	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			pTCP->closeSocket()
			) == AWE::Socket::Error::Success
		);

	AWE_SAFE_DELETE( pRemoteConn );
	AWE_SAFE_DELETE( pTCP );

	return 0;
}

// ---------------------------------------------------------------

AWE::uint32 TCP_Transfer_ClientThread::runThread()
{
	// -->> Lock
	SocketTestCase::s_kSemaphore.aquire();

	AWE::Socket::TCP::Protocol* pTCP = AWE::Socket::TCP::create();
	CPPUNIT_ASSERT( pTCP );

	// listen on our port
	AWE::Socket::Address kRemoteAddress;
	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			pTCP->resolveAddress(
				&kRemoteAddress,
				(SocketTestCase::s_bTestIP4 ? SocketTestCase::s_iServIP_v4 : SocketTestCase::s_iServIP_v6),
				g_iServerPort//,
//				(SocketTestCase::s_bTestIP4 ? AF_INET : AF_INET6)
				)
			) == AWE::Socket::Error::Success
		);

	AWE::Socket::Address kLocalAddress;
	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			pTCP->resolveLocalAddress(
				&kLocalAddress,
				0,
				(SocketTestCase::s_bTestIP4 ? AF_INET : AF_INET6)
				)
			) == AWE::Socket::Error::Success
		);

	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			pTCP->createSocket( kRemoteAddress.getAddressFamily() )
			) == AWE::Socket::Error::Success
		);

	// Bind
	AWE::Socket::StreamProtocolHost< AWE::Socket::TCP::Protocol > kHost( pTCP );
	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			kHost.bind( kLocalAddress )
			) == AWE::Socket::Error::Success
		);
	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			pTCP->getBoundAddress( &kLocalAddress )
			) == AWE::Socket::Error::Success
		);

	// Connect
	AWE::Core::String sAddress;
	AWE::uint16 iPort( 0 );

	kRemoteAddress.getAddress( &sAddress );
	kRemoteAddress.getPort( &iPort );

	std::cout	<< "[Client] Connecting to \"" << sAddress << "\""
				<< " port " << iPort
				<< std::endl << std::flush;

	AWE::Socket::StreamProtocolClient< AWE::Socket::TCP::Protocol > kClient( pTCP );

	// as we are using blocking sockets, there is a small
	// race window between the server releasing the semaphore
	// and actually calling listen on the socket
	// this is indicated by the connect returning CONNREFUSED
	// this is not an issue with the socket library but a deficiency
	// of this test
	AWE::Socket::Error::_t eError;
	do
	{
		eError = AWE::Socket::Error::convertNativeError( kClient.connect( kRemoteAddress ) );
	} while ( eError == AWE::Socket::Error::ConnectionRefused );
	CPPUNIT_ASSERT( eError == AWE::Socket::Error::Success );

	pTCP->getBoundAddress( &kLocalAddress );
	kLocalAddress.getAddress( &sAddress );
	kLocalAddress.getPort( &iPort );

	std::cout	<< "[Client] Bound to \"" << sAddress << "\""
				<< " port " << iPort
				<< std::endl << std::flush;

	// transfer some text
	AWE::uint32 sendSize( 0 );

	// send isn't guaranteed to send the entire buffer
	// so we must loop
	while ( sendSize != g_sText.length() )
	{
		int iResult = pTCP->send(
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

	pTCP->closeSocket();

	AWE_SAFE_DELETE( pTCP );

	return 0;
}

// ---------------------------------------------------------------

void SocketTestCase::Socket_IPv4_TCP_Transfer()
{
	// init sockets
	AWE::Socket::init();

	s_bTestIP4 = true;

	AWE::Core::SystemPRNG random;
	random.seed( AWE::Core::Platform::getMilliSecondsSinceSystemStart() );

	for ( AWE::uint32 i = 0; i < 10; i++ )
	{
		// threads
		TCP_Transfer_ServerThread kServerThread;
		TCP_Transfer_ClientThread kClientThread;

		kServerThread.startThread();
		kClientThread.startThread();

		CPPUNIT_ASSERT( kServerThread.joinThread() == 0 );
		CPPUNIT_ASSERT( kClientThread.joinThread() == 0 );
	}

	// shutdown sockets
	AWE::Socket::shutdown();
}

// ---------------------------------------------------------------

void SocketTestCase::Socket_IPv6_TCP_Transfer()
{
	// init sockets
	AWE::Socket::init();

	s_bTestIP4 = false;

	AWE::Core::SystemPRNG random;
	random.seed( AWE::Core::Platform::getMilliSecondsSinceSystemStart() );

	for ( AWE::uint32 i = 0; i < 10; i++ )
	{
		// threads
		TCP_Transfer_ServerThread kServerThread;
		TCP_Transfer_ClientThread kClientThread;

		kServerThread.startThread();
		kClientThread.startThread();

		CPPUNIT_ASSERT( kServerThread.joinThread() == 0 );
		CPPUNIT_ASSERT( kClientThread.joinThread() == 0 );
	}

	// shutdown sockets
	AWE::Socket::shutdown();
}

// ---------------------------------------------------------------
