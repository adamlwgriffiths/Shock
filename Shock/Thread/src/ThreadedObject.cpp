/*
 * ThreadedObject.cpp
 *
 *  Created on: 24/12/2010
 *      Author: adam
 */

#include "Shock/Thread/ThreadedObject.h"

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Assert/Assert.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Thread {

// ---------------------------------------------------------------

//namespace {

Shock::Types::size_t threadedObjectEntryFunction( void* pArg )
{
	// cast pArg to ThreadedClass
	Shock::Thread::ThreadedObject * pThreadedObject =
		(Shock::Thread::ThreadedObject *)pArg;
	SHOCK_ASSERT_EXPLODE( 0 != pThreadedObject );

	// run the threaded function
	return pThreadedObject->threadFunction();
}

//};

// ---------------------------------------------------------------

ThreadedObject::ThreadedObject() :
	m_iStackSize( 0 ),
	m_kThreadID( Shock::Consts::Thread::InvalidThreadID ),
	m_bIsRunning( false )
{
}

// ---------------------------------------------------------------

ThreadedObject::ThreadedObject( size_t const & iStackSize ) :
	m_iStackSize( iStackSize ),
	m_kThreadID( Shock::Consts::Thread::InvalidThreadID ),
	m_bIsRunning( false )
{
}

// ---------------------------------------------------------------

ThreadedObject::~ThreadedObject()
{
	// ensure we're not still running
	SHOCK_ASSERT_EXPLODE( false == m_bIsRunning );

	if ( Shock::Consts::Thread::InvalidThreadID != m_kThreadID )
	{
		// cleanup our thread handles
		Shock::Thread::cleanupThread( m_kThreadID );
	}
}

// ---------------------------------------------------------------

Shock::Thread::Error ThreadedObject::run()
{
	// check if we don't have a thread ID yet
	SHOCK_ASSERT_EXPLODE( false == m_bIsRunning );

	// check if we need to create a thread
	if ( Shock::Consts::Thread::InvalidThreadID != m_kThreadID )
	{
		// free our existing handle
		Shock::Thread::cleanupThread( m_kThreadID );
	}

	// create a thread
	m_kThreadID = Shock::Thread::createThread(
		threadedObjectEntryFunction,
		(void*)this,
		m_iStackSize
		);

	// run the thread
	Shock::Thread::Error kError(
		Shock::Thread::runThread( m_kThreadID )
		);

	return kError;
}

// ---------------------------------------------------------------

Shock::Thread::Error ThreadedObject::join(
	Shock::Time::Time * pMaxWaitTime
	)
{
	// the thread may already have completed, we must not do anything
	// that requires this
	// all we can do is check the thread was told to run

	// ensure we have a valid thread
	SHOCK_ASSERT( Shock::Consts::Thread::InvalidThreadID != m_kThreadID );

	return Shock::Thread::joinThread( m_kThreadID, pMaxWaitTime );
}

// ---------------------------------------------------------------

Shock::Types::size_t ThreadedObject::threadFunction()
{
	m_bIsRunning = true;
	Shock::Types::size_t iResult( runThread() );
	m_bIsRunning = false;
	return iResult;
}

// ---------------------------------------------------------------

Shock::Thread::ThreadID ThreadedObject::getThreadID() const
{
	return m_kThreadID;
}

// ---------------------------------------------------------------

bool ThreadedObject::isRunning() const
{
	return m_bIsRunning;
}

// ---------------------------------------------------------------

}; // namespace Thread
}; // namespace Shock

// ---------------------------------------------------------------

