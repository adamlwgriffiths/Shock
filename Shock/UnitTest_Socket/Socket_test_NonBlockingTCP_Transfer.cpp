#include <cppunit/config/SourcePrefix.h>
#include "Socket_test.h"

// Core Includes
#include "AWE/Core/Core.h"
#include "AWE/Core/SystemPRNG.h"
#include "AWE/Core/TimeConsts.h"

// Socket Includes
#include "AWE/Socket/Address.h"
#include "AWE/Socket/Socket.h"
#include "AWE/Socket/TCP.h"
#include "AWE/Socket/StreamProtocolHost.h"
#include "AWE/Socket/StreamProtocolClient.h"
#include "AWE/Socket/SocketSelector.h"

// ---------------------------------------------------------------

namespace {

AWE::Core::String	g_sText( "Hello world!" );
AWE::uint16			g_iServerPort		= 0;
AWE::uint16			g_iClientPort		= 0;
};

// ---------------------------------------------------------------

AWE::uint32 NonBlockingTCP_Transfer_ServerThread::runThread()
{
	AWE::Socket::TCP::Protocol* pTCP = AWE::Socket::TCP::create();
	CPPUNIT_ASSERT( pTCP );

	// listen on our port
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
			pTCP->createSocket( kLocalAddress.getAddressFamily() )
			) == AWE::Socket::Error::Success
		);

	// set as non-blocking
	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			pTCP->getSocket()->setNonBlocking( true )
			) == AWE::Socket::Error::Success
		);

	// select on the sockets
	AWE::Socket::SocketSelector kSelector;
	AWE::Socket::SocketSelector::SocketContainer kReadSockets;
	AWE::Socket::SocketSelector::SocketContainer kWriteSockets;
	AWE::Socket::SocketSelector::SocketContainer kExceptionSockets;

	kSelector.addReadSocket( pTCP->getSocket() );

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

	// non-blocking listen always returns success
	// it just puts the socket in a listening state
	// we have to select on the socket AFTER we've called
	// listen
	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			kHost.listen()
			) == AWE::Socket::Error::Success
		);

	SocketTestCase::s_kSemaphore.release();

	{
		// Select on the socket
		kReadSockets.clear();
		kWriteSockets.clear();
		kExceptionSockets.clear();
		AWE::uint32 iSocketsSelected( 0 );
		kSelector.select(
			kReadSockets,
			kWriteSockets,
			kExceptionSockets,
			iSocketsSelected,
			AWE::Core::TimeConsts::SECOND_IN_MICRO_SECONDS * 50 // 50 seconds
			);
		CPPUNIT_ASSERT( iSocketsSelected == 1 );
		// listen success results in a read socket
		CPPUNIT_ASSERT( kReadSockets.size() == 1 );
		// write cannot be called as this socket is not connected
		// but we haven't added it to the list anyway
		CPPUNIT_ASSERT( kWriteSockets.size() == 0 );
		CPPUNIT_ASSERT( kExceptionSockets.size() == 0 );
	}

	// accept the connection
	AWE::Socket::Address kRemoteAddress;
	AWE::Socket::TCP::Protocol* pRemoteConn = 0;
	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			kHost.accept( &pRemoteConn, &kRemoteAddress )
			) == AWE::Socket::Error::Success
		);
	CPPUNIT_ASSERT( pRemoteConn );

	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			pRemoteConn->getSocket()->setNonBlocking( true )
			) == AWE::Socket::Error::Success
		);

	// add the socket to our selector
	kSelector.addReadSocket( pRemoteConn->getSocket() );
//	kSelector.addWriteSocket( pRemoteConn->getSocket() );
//	kSelector.addExceptionSocket( pRemoteConn->getSocket() );

	kRemoteAddress.getAddress( &sAddress );
	kRemoteAddress.getPort( &iPort );

	std::cout	<< "[Server] Received connection from IP \"" << sAddress << "\""
				<< " port " << iPort
				<< std::endl << std::flush;

	// receive some data
	const AWE::uint32 dataSize( 100 );
	AWE::int8 pData[ dataSize ];
	memset( pData, 0, dataSize );

	// wait for the socket to receive some data
	{
		// Select on the socket
		kReadSockets.clear();
		kWriteSockets.clear();
		kExceptionSockets.clear();
		AWE::uint32 iSocketsSelected( 0 );
		kSelector.select(
			kReadSockets,
			kWriteSockets,
			kExceptionSockets,
			iSocketsSelected,
			AWE::Core::TimeConsts::SECOND_IN_MICRO_SECONDS
			);
		// this would be 2 if the new socket was also in the "write" list
		CPPUNIT_ASSERT( iSocketsSelected == 1 );
		// once there is enough data for a receive call to succeed
		// select will return the socket as a read socket
		// at this point, receive will succeed
		CPPUNIT_ASSERT( kReadSockets.size() == 1 );
		// this socket can be written to as it is connected
		// however, it isn't in the list
		CPPUNIT_ASSERT( kWriteSockets.size() == 0 );
		CPPUNIT_ASSERT( kExceptionSockets.size() == 0 );
	}

	// data has arrived
	// we can read it straight out
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

	kSelector.removeReadSocket( pTCP->getSocket() );
//	kSelector.removeWriteSocket( pTCP->getSocket() );
//	kSelector.removeExceptionSocket( pTCP->getSocket() );

	kSelector.removeReadSocket( pRemoteConn->getSocket() );
//	kSelector.removeWriteSocket( pRemoteConn->getSocket() );
//	kSelector.removeExceptionSocket( pRemoteConn->getSocket() );

	CPPUNIT_ASSERT( pRemoteConn->closeSocket() == 0 );
	CPPUNIT_ASSERT( pTCP->closeSocket() == 0 );

	AWE_SAFE_DELETE( pRemoteConn );
	AWE_SAFE_DELETE( pTCP );

	return 0;
}

// ---------------------------------------------------------------

AWE::uint32 NonBlockingTCP_Transfer_ClientThread::runThread()
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

	// set as non-blocking
	CPPUNIT_ASSERT(
		AWE::Socket::Error::convertNativeError(
			pTCP->getSocket()->setNonBlocking( true )
			) == AWE::Socket::Error::Success
		);

	// select on the sockets
	AWE::Socket::SocketSelector kSelector;
	AWE::Socket::SocketSelector::SocketContainer kReadSockets;
	AWE::Socket::SocketSelector::SocketContainer kWriteSockets;
	AWE::Socket::SocketSelector::SocketContainer kExceptionSockets;

	kSelector.addReadSocket( pTCP->getSocket() );
	kSelector.addWriteSocket( pTCP->getSocket() );
	kSelector.addExceptionSocket( pTCP->getSocket() );

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

	AWE::Socket::Error::_t eError = AWE::Socket::Error::convertNativeError(
		kClient.connect( kRemoteAddress )
		);
	// Windows returns "OperationInProgress" for non-blocking connect
	// Linux returns "WouldBlock" for non-blocking connect
	CPPUNIT_ASSERT(
		eError == AWE::Socket::Error::OperationInProgress ||
		eError == AWE::Socket::Error::WouldBlock
		);

	{
		// Select on the socket
		kReadSockets.clear();
		kWriteSockets.clear();
		kExceptionSockets.clear();
		AWE::uint32 iSocketsSelected( 0 );
		kSelector.select(
			kReadSockets,
			kWriteSockets,
			kExceptionSockets,
			iSocketsSelected,
			AWE::Core::TimeConsts::SECOND_IN_MICRO_SECONDS
			);
		CPPUNIT_ASSERT( iSocketsSelected == 1 );
		// connect success results in a write socket
		CPPUNIT_ASSERT( kReadSockets.size() == 0 );
		CPPUNIT_ASSERT( kWriteSockets.size() == 1 );
		CPPUNIT_ASSERT( kExceptionSockets.size() == 0 );
	}

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

	kSelector.removeReadSocket( pTCP->getSocket() );
	kSelector.removeWriteSocket( pTCP->getSocket() );
	kSelector.removeExceptionSocket( pTCP->getSocket() );

	pTCP->closeSocket();

	AWE_SAFE_DELETE( pTCP );

	return 0;
}

// ---------------------------------------------------------------

void SocketTestCase::Socket_IPv4_NonBlockingTCP_Transfer()
{
	// init sockets
	AWE::Socket::init();

	s_bTestIP4 = true;

	AWE::Core::SystemPRNG random;
	random.seed( AWE::Core::Platform::getMilliSecondsSinceSystemStart() );

	for ( AWE::uint32 i = 0; i < 10; i++ )
	{
		// threads
		NonBlockingTCP_Transfer_ServerThread kServerThread;
		NonBlockingTCP_Transfer_ClientThread kClientThread;

		kServerThread.startThread();
		kClientThread.startThread();

		CPPUNIT_ASSERT( kServerThread.joinThread() == 0 );
		CPPUNIT_ASSERT( kClientThread.joinThread() == 0 );
	}

	// shutdown sockets
	AWE::Socket::shutdown();
}

// ---------------------------------------------------------------

void SocketTestCase::Socket_IPv6_NonBlockingTCP_Transfer()
{
	// init sockets
	AWE::Socket::init();

	s_bTestIP4 = false;

	AWE::Core::SystemPRNG random;
	random.seed( AWE::Core::Platform::getMilliSecondsSinceSystemStart() );

	for ( AWE::uint32 i = 0; i < 10; i++ )
	{
		// threads
		NonBlockingTCP_Transfer_ServerThread kServerThread;
		NonBlockingTCP_Transfer_ClientThread kClientThread;

		kServerThread.startThread();
		kClientThread.startThread();

		CPPUNIT_ASSERT( kServerThread.joinThread() == 0 );
		CPPUNIT_ASSERT( kClientThread.joinThread() == 0 );
	}

	// shutdown sockets
	AWE::Socket::shutdown();
}

// ---------------------------------------------------------------
