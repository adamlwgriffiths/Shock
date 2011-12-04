/*
 * ScopedMutexLock.h
 *
 *  Created on: 15/12/2010
 *      Author: adam
 */

#ifndef SCOPEDMUTEXLOCK_H_
#define SCOPEDMUTEXLOCK_H_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Thread/Mutex.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Thread {

// ---------------------------------------------------------------

class ScopedMutexLock
{
	public:
		ScopedMutexLock(
			Shock::Thread::Mutex & kMutex
			);
		~ScopedMutexLock();

	protected:
		Shock::Thread::Mutex &		m_kMutex;
};

// ---------------------------------------------------------------

}; // namespace Thread
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* SCOPEDMUTEXLOCK_H_ */
