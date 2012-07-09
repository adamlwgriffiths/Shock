#include <cppunit/config/SourcePrefix.h>
#include "test_Ping.h"

// ---------------------------------------------------------------

// Network Includes
#include "AWE/Ping/Ping.h"

// ---------------------------------------------------------------

CPPUNIT_TEST_SUITE_REGISTRATION( PingTestCase );

// ---------------------------------------------------------------

void PingTestCase::Network_Ping()
{
	//try
	{
		AWE::Ping::Ping kPing( /*"127.0.0.1"*/ "www.google.com" );
		//AWE::Network::Ping kPing( "ipv6.google.com" ); // requires ipv6 enabled network + gateway + ISP

		CPPUNIT_ASSERT(
			AWE::Socket::Error::convertNativeError(
				kPing.init()
				) == AWE::Socket::Error::Success
			);

		kPing.setTimeout( 1000 );

		CPPUNIT_ASSERT(
			AWE::Socket::Error::convertNativeError(
				kPing.ping()
				) == AWE::Socket::Error::Success
			);

		kPing.shutdown();
	}
	//catch ( AWE::Core::Exception& /*kException*/ )
	//{
	//	int i = 0;
	//	CPPUNIT_ASSERT(0);
	//}
}

// ---------------------------------------------------------------
