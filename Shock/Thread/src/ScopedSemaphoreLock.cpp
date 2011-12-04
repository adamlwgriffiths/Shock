/*
 * ScopedSemaphoreLock.cpp
 *
 *  Created on: 16/12/2010
 *      Author: adam
 */

#include "Shock/Thread/ScopedSemaphoreLock.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Thread {

// ---------------------------------------------------------------

ScopedSemaphoreLock::ScopedSemaphoreLock(
	Shock::Thread::Semaphore & kSemaphore
	) :
	m_kSemaphore( kSemaphore )
{
	m_kSemaphore.acquire();
}

// ---------------------------------------------------------------

ScopedSemaphoreLock::~ScopedSemaphoreLock()
{
	m_kSemaphore.release();
}

// ---------------------------------------------------------------

}; // namespace Thread
}; // namespace Shock

// ---------------------------------------------------------------
