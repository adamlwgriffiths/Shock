#ifndef PING_TEST_H
#define PING_TEST_H

// ---------------------------------------------------------------
// CPP Unit Includes
#include <cppunit/extensions/HelperMacros.h>

// ---------------------------------------------------------------

class PingTestCase : public CPPUNIT_NS::TestFixture
{
		CPPUNIT_TEST_SUITE( PingTestCase );
		CPPUNIT_TEST( Network_Ping );
		CPPUNIT_TEST_SUITE_END();

	protected:
		// proper usage
		void Network_Ping();
};

// ---------------------------------------------------------------

#endif
