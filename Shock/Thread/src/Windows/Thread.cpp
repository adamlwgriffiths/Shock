/*
 * Thread.cpp
 *
 *  Created on: 03/07/2010
 *      Author: Adam Griffiths
 */

#include "Shock/Thread/Thread.h"

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Assert/Assert.h"
#include "Shock/Platform/Platform.h"
#include "Shock/Platform/Memory.h"
#include "Shock/Types/Limits.h"
#include "Shock/Types/Conversion.h"

// ---------------------------------------------------------------
// Private namespace
namespace {

// ---------------------------------------------------------------
// Typedefs

// Used to pass the thread function and any parameters into
// our thread wrapper
typedef std::pair< Shock::Thread::ThreadFunc, void* >	ThreadFuncData;

// ---------------------------------------------------------------

namespace RunThreadResult
{
	enum _t
	{
		FailureMax						= -1,
		NotSuspended					= 0,
		Success								= 1,
		StillSuspendedMin			= 2,
	};
};

// ---------------------------------------------------------------

namespace SuspendThreadResult
{
	enum _t
	{
		FailureMax						= -1,
		SuccessMin						= 0,
	};
};

// ---------------------------------------------------------------

}; // namespace

// ---------------------------------------------------------------

namespace Shock {
namespace Thread {

// ---------------------------------------------------------------

namespace {

DWORD WINAPI threadEntryPoint( LPVOID pData )
{
	ThreadFuncData* pFuncData = (ThreadFuncData*)pData;
	SHOCK_ASSERT( pFuncData );

	Shock::Thread::ThreadFunc pFunc = pFuncData->first;
	void* pParam = pFuncData->second;

	SHOCK_ASSERT( pFunc );

	// free struct
	SHOCK_SAFE_DELETE( pFuncData );

	DWORD iResult(0);

	// run the function with some safe guards
	try
	{
		// run the function
		iResult = (DWORD)(*pFunc)( pParam );
	}
	catch ( std::exception & /*e*/ )
	{
		// TODO: print exception message and exit gracefully
		// log a message and exit gracefully
		SHOCK_EXPLODE_MSG( "Unhandled exception in thread" );
	}

	return iResult;
}

};

// ---------------------------------------------------------------

ThreadID createThread(
	ThreadFunc pThreadFunc,
	void* pParam,
	Shock::Types::size_t const & iStackSize
	)
{
	// TODO: replace with non-heap based solution
	// preferably pass pParam in AFTER thread creation
	// and use some sort of locking mechanism?
	ThreadFuncData* pFuncData = new ThreadFuncData();
	pFuncData->first = pThreadFunc;
	pFuncData->second = pParam;

	// create the thread
	// don't run it immediately
	// http://msdn.microsoft.com/en-us/library/ms682453(VS.85).aspx
	ThreadID kHandle = ::CreateThread(
		0,							// thread attributes
		iStackSize,					// stack size in bytes, 0 means default of executable
		threadEntryPoint,			// entry point
		pFuncData,					// parameter for entry point
		CREATE_SUSPENDED,			// creation flags
		0							// thread id pointer
		);

	pFuncData = 0;

	return kHandle;
}

// ---------------------------------------------------------------

void cleanupThread(
	ThreadID & kThreadID
	)
{
	// this function will not block if the thread is still running
	// TODO: compare with posix, if posix blocks, make this block too

	// TODO: check for errors
	// close the handle
	::CloseHandle( kThreadID );

	// set the handle as invalid
	kThreadID = Shock::Consts::Thread::InvalidThreadID;
}

// ---------------------------------------------------------------

Shock::Thread::Error runThread(
	ThreadID const & kThreadID
	)
{
	Shock::Thread::Error kResult(
		Shock::Consts::Thread::Error::Success
		);

	// -1 = failure, call getLastError, invalid thread?
	//  0 = thread not suspended previously
	//  1 = success
	// >1 = thread is still suspended, try again later?
	// http://msdn.microsoft.com/en-us/library/ms685086(VS.85).aspx
	// HANDLE is a typedef void*
	DWORD iResult(
		::ResumeThread( kThreadID )
		);

	if ( iResult == (DWORD)RunThreadResult::Success )
	{
		kResult.setError( Shock::Consts::Thread::Error::Success );
	}
	else if ( iResult == (DWORD)RunThreadResult::NotSuspended )
	{
		kResult.setError( Shock::Consts::Thread::Error::ThreadNotSuspended );
	}
	else if ( iResult <= (DWORD)RunThreadResult::FailureMax )
	{
		kResult.setError( Shock::Consts::Thread::Error::Error );
	}
	else if ( iResult >= (DWORD)RunThreadResult::StillSuspendedMin )
	{
		kResult.setError( Shock::Consts::Thread::Error::ResumeFailed );
	}

	return kResult;
}

// ---------------------------------------------------------------

Shock::Thread::Error joinThread(
	ThreadID const & kThreadID,
	Shock::Time::Time * pMaxWaitTime
	)
{
	Shock::Thread::Error kResult( Shock::Consts::Thread::Error::Success );
	Shock::Types::uint64_t iWaitTime( 0 );

	if ( 0 != pMaxWaitTime )
	{
		Shock::Time::Base kBase( Shock::Time::Base::MilliSeconds );
		Shock::Types::ConversionError kTimeError;

		// get the time as the appropriate base
		// ignore underflow errors
		iWaitTime = pMaxWaitTime->getTime(
			kBase,
			kTimeError
			);
	}
	else
	{
		iWaitTime = INFINITE;
	}


	// INFINITE = waits until object ready
	// 0  = leaves immediately if not ready
	// >0 = waits until object ready or time expired
	// http://msdn.microsoft.com/en-us/library/ms687032(VS.85).aspx
	Shock::Types::uint32_t iResult(
		::WaitForSingleObject(
			kThreadID,				// thread handle
			iWaitTime					// time in milliseconds
			)
		);

	if ( WAIT_OBJECT_0 == iResult )
	{
		kResult.setError( Shock::Consts::Thread::Error::Success );
	}
	else if ( WAIT_TIMEOUT == iResult )
	{
		kResult.setError( Shock::Consts::Thread::Error::Timeout );
	}
	else
	{
		kResult.setError( Shock::Consts::Thread::Error::Error );
	}


	return kResult;
}

// ---------------------------------------------------------------

ThreadID getCurrentThreadID()
{
	return static_cast< Shock::Thread::ThreadID >(
		GetCurrentThread()
		);
}

// ---------------------------------------------------------------

}; // namespace Threads
}; // namespace Shock

// ---------------------------------------------------------------
