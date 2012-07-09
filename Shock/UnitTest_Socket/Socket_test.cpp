#include <cppunit/config/SourcePrefix.h>
#include "Socket_test.h"

// ---------------------------------------------------------------

CPPUNIT_TEST_SUITE_REGISTRATION( SocketTestCase );

// ---------------------------------------------------------------

// http://en.wikipedia.org/wiki/IPv6#Special_addresses
// bind to - :: ip6, 0.0.0.0 ip4
// connect to ::1 ip6, 127.0.0.1 ip4
const AWE::int8			SocketTestCase::s_iServBindIP_v4[]			= "0.0.0.0";
const AWE::int8			SocketTestCase::s_iServBindIP_v6[]			= "::";

const AWE::int8			SocketTestCase::s_iServIP_v4[]				= "127.0.0.1";
const AWE::int8			SocketTestCase::s_iServIP_v6[]				= "::1";

bool					SocketTestCase::s_bTestIP4					= true;

AWE::Core::LocalSemaphore	SocketTestCase::s_kSemaphore( "TestLock", 0 );

// ---------------------------------------------------------------

