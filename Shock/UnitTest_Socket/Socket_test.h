#ifndef SOCKET_TEST_H
#define SOCKET_TEST_H

// ---------------------------------------------------------------
// CPP Unit Includes
#include <cppunit/extensions/HelperMacros.h>

// Core Includes
#include "AWE/Core/ThreadedClass.h"
#include "AWE/Core/LocalSemaphore.h"

// ---------------------------------------------------------------

#define WAIT_BEFORE_DESTROY

class SocketTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( SocketTestCase );
	CPPUNIT_TEST( Socket_IPv4_UDP_Transfer );
#if defined(AWE_IPV6_ENABLED)
	CPPUNIT_TEST( Socket_IPv6_UDP_Transfer );
#endif
	CPPUNIT_TEST( Socket_IPv4_TCP_Transfer );
#if defined(AWE_IPV6_ENABLED)
	CPPUNIT_TEST( Socket_IPv6_TCP_Transfer );
#endif
	CPPUNIT_TEST( Socket_IPv4_NonBlockingTCP_Transfer );
#if defined(AWE_IPV6_ENABLED)
	CPPUNIT_TEST( Socket_IPv6_NonBlockingTCP_Transfer );
#endif
	CPPUNIT_TEST_SUITE_END();

	public:
		static const AWE::int8			s_iServBindIP_v4[];
		static const AWE::int8			s_iServBindIP_v6[];
		static const AWE::int8			s_iServIP_v4[];
		static const AWE::int8			s_iServIP_v6[];
		static AWE::Core::LocalSemaphore	s_kSemaphore;
		static bool						s_bTestIP4;

	protected:
		// proper usage

		// TCP
		void Socket_IPv4_TCP_Transfer();
		void Socket_IPv6_TCP_Transfer();
		void Socket_IPv4_NonBlockingTCP_Transfer();
		void Socket_IPv6_NonBlockingTCP_Transfer();

		// UDP
		void Socket_IPv4_UDP_Transfer();
		void Socket_IPv6_UDP_Transfer();
};

// ---------------------------------------------------------------

class TCP_Transfer_ClientThread :
	public AWE::Core::ThreadedClass
{
	protected:
		virtual AWE::uint32		runThread();
};

// ---------------------------------------------------------------

class TCP_Transfer_ServerThread :
	public AWE::Core::ThreadedClass
{
	protected:
		virtual AWE::uint32		runThread();
};

// ---------------------------------------------------------------

class NonBlockingTCP_Transfer_ClientThread :
	public AWE::Core::ThreadedClass
{
	protected:
		virtual AWE::uint32		runThread();
};

// ---------------------------------------------------------------

class NonBlockingTCP_Transfer_ServerThread :
	public AWE::Core::ThreadedClass
{
	protected:
		virtual AWE::uint32		runThread();
};

// ---------------------------------------------------------------

class UDP_Transfer_ClientThread :
	public AWE::Core::ThreadedClass
{
	protected:
		virtual AWE::uint32		runThread();
};

// ---------------------------------------------------------------

class UDP_Transfer_ServerThread :
	public AWE::Core::ThreadedClass
{
	protected:
		virtual AWE::uint32		runThread();
};

// ---------------------------------------------------------------

#endif
