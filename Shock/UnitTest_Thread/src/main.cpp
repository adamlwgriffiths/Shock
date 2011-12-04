/*
 * main.cpp
 *
 *  Created on: 28/12/2010
 *      Author: adam
 */

// ---------------------------------------------------------------
// System Includes
#include <cstdio>
#include <iostream>

// Shock Includes
#include "Shock/Types/Types.h"
#include "Shock/Assert/Assert.h"
#include "Shock/Thread/Thread.h"
#include "Shock/Thread/Mutex.h"
#include "Shock/Thread/ScopedMutexLock.h"
#include "Shock/Thread/ThreadedObject.h"

// ---------------------------------------------------------------

namespace {

Shock::Types::uint32_t			g_iValue( 0 );
Shock::Types::size_t const		g_iLoopCount( 100 );
Shock::Thread::Mutex			g_kMutex;

// ---------------------------------------------------------------

Shock::Types::size_t threadTest( void* pArg )
{
	Shock::Types::uint32_t const iThreadValue( *((Shock::Types::uint32_t*)(pArg)) );

	g_iValue = iThreadValue;
	for ( Shock::Types::size_t count( 0 ); count < g_iLoopCount; ++count )
	{
		while ( iThreadValue == g_iValue )
		{
			// wait
		}
		std::cout
			<< "["
			<< iThreadValue
			<< "] - "
			<< "Value = "
			<< g_iValue
			<< ", setting value to "
			<< iThreadValue
			<< std::endl
			<< std::flush;

		g_iValue = iThreadValue;
	}

	return 0;
}

// ---------------------------------------------------------------

Shock::Types::size_t threadTestMutex( void* pArg )
{
	// -->> Lock
	Shock::Thread::ScopedMutexLock kLock( g_kMutex );

	Shock::Types::uint32_t const iThreadValue( *((Shock::Types::uint32_t*)(pArg)) );

	std::cout
		<< "["
		<< iThreadValue
		<< "] - "
		<< "Mutex obtained, writing values"
		<< std::endl
		<< std::flush;

	g_iValue = iThreadValue;
	for ( Shock::Types::size_t count( 0 ); count < g_iLoopCount; ++count )
	{
		SHOCK_ASSERT( g_iValue == iThreadValue );
		g_iValue = iThreadValue;
	}

	std::cout
		<< "["
		<< iThreadValue
		<< "] - "
		<< "Mutex released"
		<< std::endl
		<< std::flush;

	return 0;
	// <<-- Unlock
}

// ---------------------------------------------------------------

class ThreadedObjectTest :
	public Shock::Thread::ThreadedObject
{
	public:
		ThreadedObjectTest( Shock::Types::uint32_t iThreadValue ) :
			Shock::Thread::ThreadedObject(),
			m_iThreadValue( iThreadValue )
		{
		};

		~ThreadedObjectTest()
		{
		};

	private:
		virtual Shock::Types::size_t	runThread()
		{
			g_iValue = m_iThreadValue;
			for ( Shock::Types::size_t count( 0 ); count < g_iLoopCount; ++count )
			{
				while ( m_iThreadValue == g_iValue )
				{
					// wait
				}
				std::cout
					<< "["
					<< m_iThreadValue
					<< "] - "
					<< "Value = "
					<< g_iValue
					<< ", setting value to "
					<< m_iThreadValue
					<< std::endl
					<< std::flush;

				g_iValue = m_iThreadValue;
			}

			return 0;
		};

		Shock::Types::uint32_t		m_iThreadValue;
};

// ---------------------------------------------------------------

}; // namespace

// ---------------------------------------------------------------

int main( int argc, char* argv[] )
{
	std::cout
		<< "Unit Test: Shock::Thread"
		<< std::endl
		<< std::flush;

	// thread functions
	{
		// create threads
		Shock::Types::uint32_t const iThread1_Value( 1 );
		Shock::Types::uint32_t const iThread2_Value( 2 );

		Shock::Thread::ThreadID kThread1(
			Shock::Thread::createThread(
				threadTest,
				(void*)&iThread1_Value
				)
			);
		Shock::Thread::ThreadID kThread2(
			Shock::Thread::createThread(
				threadTest,
				(void*)&iThread2_Value
				)
			);

		// run threads
		Shock::Thread::Error kError(
			Shock::Consts::Thread::Error::Success
			);

		kError = Shock::Thread::runThread( kThread1 );
		SHOCK_ASSERT( Shock::Consts::Thread::Error::Success == kError );

		kError = Shock::Thread::runThread( kThread2 );
		SHOCK_ASSERT( Shock::Consts::Thread::Error::Success == kError );

		// join threads
		kError = Shock::Thread::joinThread( kThread1 );
		SHOCK_ASSERT( Shock::Consts::Thread::Error::Success == kError );

		kError = Shock::Thread::joinThread( kThread2 );
		SHOCK_ASSERT( Shock::Consts::Thread::Error::Success == kError );

		// destroy threads
		Shock::Thread::cleanupThread( kThread1 );
		Shock::Thread::cleanupThread( kThread2 );
	}

	// thread exclusivity
	{
		// create threads
		Shock::Types::uint32_t const iThread1_Value( 1 );
		Shock::Types::uint32_t const iThread2_Value( 2 );

		Shock::Thread::ThreadID kThread1(
			Shock::Thread::createThread(
				threadTestMutex,
				(void*)&iThread1_Value
				)
			);
		Shock::Thread::ThreadID kThread2(
			Shock::Thread::createThread(
				threadTestMutex,
				(void*)&iThread2_Value
				)
			);

		// run threads
		Shock::Thread::Error kError(
			Shock::Consts::Thread::Error::Success
			);

		kError = Shock::Thread::runThread( kThread1 );
		SHOCK_ASSERT( Shock::Consts::Thread::Error::Success == kError );

		kError = Shock::Thread::runThread( kThread2 );
		SHOCK_ASSERT( Shock::Consts::Thread::Error::Success == kError );

		// join threads
		kError = Shock::Thread::joinThread( kThread1 );
		SHOCK_ASSERT( Shock::Consts::Thread::Error::Success == kError );

		kError = Shock::Thread::joinThread( kThread2 );
		SHOCK_ASSERT( Shock::Consts::Thread::Error::Success == kError );

		// destroy threads
		Shock::Thread::cleanupThread( kThread1 );
		Shock::Thread::cleanupThread( kThread2 );
	}

	// threaded object
	{
		ThreadedObjectTest kThread1( 1 );
		ThreadedObjectTest kThread2( 2 );

		// run the threads
		kThread1.run();
		kThread2.run();

		// join threads
		kThread1.join();
		kThread2.join();
	}

	// Complete
	std::cout
		<< "Press enter to continue..."
		<< std::endl
		<< std::flush;
	getchar();

	return 0;
}

// ---------------------------------------------------------------
