/*
 * Semaphore.cpp
 *
 *  Created on: 15/12/2010
 *      Author: adam
 */

#include "Shock/Thread/Semaphore.h"

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Assert/Assert.h"
#include "Shock/Types/Limits.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Thread {

// ---------------------------------------------------------------

Semaphore::Semaphore(
	Shock::Types::size_t iInitialCount
	) :
	m_kSemaphore( 0 )
{
	m_kSemaphore = CreateSemaphore(
		0,								// Security attributes
		iInitialCount,					// Initial count
		Shock::Consts::Types::Int32::Max,	// Maximum count
		0								// name, if a name is set, it must be unique throughout the system
		);

	if ( 0 == m_kSemaphore )
	{
		// error while creating mutex
		Shock::Types::uint32_t iError( GetLastError() );

		// http://msdn.microsoft.com/en-us/library/ms682411(VS.85).aspx
		switch ( iError )
		{
			case ERROR_ALREADY_EXISTS:		// called if the mutex already exists
			case ERROR_ACCESS_DENIED:		// called if the mutex already exists and the user doesn't have enough permissions
			{
				// TODO: change these to exceptions
				SHOCK_EXPLODE_MSG(
					"A semaphore with this name already exists in this system"
					);
			} break;

			default:
			{
				SHOCK_EXPLODE_MSG(
					"Failed to create a new semaphore"
					);
			} break;
		}
	}
}

// ---------------------------------------------------------------

Semaphore::~Semaphore()
{
	CloseHandle( m_kSemaphore );
}

// ---------------------------------------------------------------

void Semaphore::acquire()
{
	Shock::Types::uint32_t iWaitResult(
		WaitForSingleObject(
			m_kSemaphore,
			INFINITE	// timeout, -1 indicates INFINITE
			)
		);

	switch ( iWaitResult )
	{
		// The thread got ownership of the mutex
		case WAIT_OBJECT_0:
		{
			// success
		} break;

		// The thread got ownership of an abandoned mutex
		// The database is in an indeterminate state
		case WAIT_ABANDONED:
		{
			SHOCK_EXPLODE_MSG(
				"Semaphore in invalid state"
				);
		} break;

		// Timeout exceeded, object not aquired
		case WAIT_TIMEOUT:
		{
			// timeout exceeded
			// shouldn't get here
			SHOCK_EXPLODE_MSG(
				"Semaphore aquire timed out, shouldn't get here!"
				);
		} break;

		// unknown result
		default:
		{
			SHOCK_EXPLODE_MSG(
				"Unknown WaitForSingleObject result for semaphore"
				);
		} break;
	}
}

// ---------------------------------------------------------------

bool Semaphore::tryAquire()
{
	bool bResult( false );

	Shock::Types::uint32_t iWaitResult(
		WaitForSingleObject(
			m_kSemaphore,
			0	// timeout, -1 indicates INFINITE
			)
		);

	switch ( iWaitResult )
	{
		// The thread got ownership of the mutex
		case WAIT_OBJECT_0:
		{
			// success
			bResult = true;
		} break;

		// The thread got ownership of an abandoned mutex
		// The database is in an indeterminate state
		case WAIT_ABANDONED:
		{
			SHOCK_EXPLODE_MSG(
				"Semaphore in invalid state"
				);
		} break;

		// Timeout exceeded, object not aquired
		case WAIT_TIMEOUT:
		{
			// timeout exceeded
			// shouldn't get here
			bResult = false;
		} break;

		// unknown result
		default:
		{
			SHOCK_EXPLODE_MSG(
				"Unknown WaitForSingleObject result for semaphore"
				);
		} break;
	}

	return bResult;
}

// ---------------------------------------------------------------

void Semaphore::release()
{
	// release a single semaphore
	Shock::Types::int32_t iPreviousCount( 0 );
	if (
		ReleaseSemaphore(
			m_kSemaphore,						// [in]		semaphore
			1,									// [in]		release count
			(LPLONG)&iPreviousCount				// [out]	LPLONGprevious count
			) == false
		)
	{
		SHOCK_EXPLODE_MSG(
			"Failed to release semaphore"
			);
	}
}

// ---------------------------------------------------------------

}; // namespace Thread
}; // namespace Shock

// ---------------------------------------------------------------

