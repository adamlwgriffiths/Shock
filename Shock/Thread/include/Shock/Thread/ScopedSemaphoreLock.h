/*
 * ScopedSemaphoreLock.h
 *
 *  Created on: 16/12/2010
 *      Author: adam
 */

#ifndef SCOPEDSEMAPHORELOCK_H_
#define SCOPEDSEMAPHORELOCK_H_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Thread/Semaphore.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Thread {

// ---------------------------------------------------------------

class ScopedSemaphoreLock
{
	public:
		ScopedSemaphoreLock(
			Shock::Thread::Semaphore & kSemaphore
			);
		~ScopedSemaphoreLock();

	protected:
		Shock::Thread::Semaphore &		m_kSemaphore;
};

// ---------------------------------------------------------------

}; // namespace Thread
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* SCOPEDSEMAPHORELOCK_H_ */
