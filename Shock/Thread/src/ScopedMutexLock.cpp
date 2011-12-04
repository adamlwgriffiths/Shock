/*
 * ScopedMutexLock.cpp
 *
 *  Created on: 16/12/2010
 *      Author: adam
 */

#include "Shock/Thread/ScopedMutexLock.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Thread {

// ---------------------------------------------------------------

ScopedMutexLock::ScopedMutexLock(
	Shock::Thread::Mutex & kMutex
	) :
	m_kMutex( kMutex )
{
	m_kMutex.acquire();
}

// ---------------------------------------------------------------

ScopedMutexLock::~ScopedMutexLock()
{
	m_kMutex.release();
}

// ---------------------------------------------------------------

}; // namespace Thread
}; // namespace Shock

// ---------------------------------------------------------------
