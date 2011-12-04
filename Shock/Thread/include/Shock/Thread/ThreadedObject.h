/*
 * ThreadedObject.h
 *
 *  Created on: 24/12/2010
 *      Author: adam
 */

#ifndef THREADEDOBJECT_H_
#define THREADEDOBJECT_H_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Thread/Thread.h"
#include "Shock/Time/Time.h"
#include "Shock/Types/Types.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Thread {

// ---------------------------------------------------------------

// TODO: check if we need to close the thread handle on exit. this would also require a new thread function
// TODO: check if a thread handle is re-usable after creation
class ThreadedObject
{
	friend Shock::Types::size_t threadedObjectEntryFunction( void* pArg );

	public:
	Shock::Thread::Error		run();
		Shock::Thread::Error	join(
			Shock::Time::Time * pMaxWaitTime = 0
			);

		bool					isRunning() const;
		Shock::Thread::ThreadID	getThreadID() const;

	protected:
		ThreadedObject();
		explicit ThreadedObject( Shock::Types::size_t const & iStackSize );
		virtual ~ThreadedObject();

		virtual Shock::Types::size_t	runThread() = 0;

	private:
		Shock::Types::size_t	threadFunction();

		Shock::Types::size_t		m_iStackSize;
		Shock::Thread::ThreadID		m_kThreadID;
		volatile bool				m_bIsRunning;
};

// ---------------------------------------------------------------

}; // namespace Thread
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* THREADEDOBJECT_H_ */
