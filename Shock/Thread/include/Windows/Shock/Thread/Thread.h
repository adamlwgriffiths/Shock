/*
 * Thread.h
 *
 *  Created on: 04/07/2010
 *      Author: Adam Griffiths
 */

#ifndef THREAD_H_
#define THREAD_H_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Thread/ThreadCommon.h"
#include "Shock/Platform/Platform.h"
#include "Shock/Time/Time.h"
#include "Shock/Types/Types.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Thread {
namespace Windows {

// ---------------------------------------------------------------
// Typedefs
typedef HANDLE		ThreadID;

// ---------------------------------------------------------------

}; // namespace Windows

// ---------------------------------------------------------------

typedef Shock::Thread::Windows::ThreadID		ThreadID;

// ---------------------------------------------------------------

}; // namespace Thread
}; // namespace Shock

// ---------------------------------------------------------------

namespace Shock {
namespace Consts {
namespace Thread {

// ---------------------------------------------------------------

Shock::Thread::ThreadID const InvalidThreadID( 0 );

// ---------------------------------------------------------------

}; // namespace Thread
}; // namespace Consts
}; // namespace Shock

// ---------------------------------------------------------------

namespace Shock {
namespace Thread {

// ---------------------------------------------------------------
// Typedefs
// Return type must be uint32_t on windows
typedef Shock::Types::size_t		(*ThreadFunc)( void* pArg );

// ---------------------------------------------------------------
// TODO: add a getThreadState function
// http://msdn.microsoft.com/en-us/library/system.threading.thread.threadstate(VS.71).aspx

ThreadID						createThread(
	ThreadFunc pThreadFunc,
	void* pParam = 0,
	Shock::Types::size_t const & iStackSize = 0
	);

void							cleanupThread(
	ThreadID & kThreadID
	);

Shock::Thread::Error			runThread(
	ThreadID const & kThreadID
	);

// a null pointer for pMaxWaitTime indicates infinity
Shock::Thread::Error			joinThread(
	ThreadID const & kThreadID,
	Shock::Time::Time * pMaxWaitTime = 0
	);

ThreadID						getCurrentThreadID();

// ---------------------------------------------------------------

}; // namespace Thread
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* THREAD_H_ */
