/*
 * Mutex
 *
 *  Created on: 15/12/2010
 *      Author: adam
 */

#include "Shock/Thread/Mutex.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Thread {

// ---------------------------------------------------------------

Mutex::Mutex() :
	m_kCriticalSection()
{
	InitializeCriticalSection( &m_kCriticalSection );
}

// ---------------------------------------------------------------

Mutex::~Mutex()
{
	// http://msdn.microsoft.com/en-us/library/ms686360(VS.85).aspx
	DeleteCriticalSection( &m_kCriticalSection );
}

// ---------------------------------------------------------------

void Mutex::acquire()
{
	EnterCriticalSection( &m_kCriticalSection );
}

// ---------------------------------------------------------------

bool Mutex::tryAquire()
{
	bool bResult(
		TryEnterCriticalSection( &m_kCriticalSection ) == TRUE ?
			true :
			false
		);
	return bResult;
}

// ---------------------------------------------------------------

void Mutex::release()
{
	LeaveCriticalSection( &m_kCriticalSection );
}

// ---------------------------------------------------------------

}; // namespace Thread
}; // namespace Shock

// ---------------------------------------------------------------

