/*
 * Singleton.hxx
 *
 *  Created on: 15/12/2010
 *      Author: adam
 */

#ifndef SINGLETON_HXX_
#define SINGLETON_HXX_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Thread/ScopedMutexLock.h"
#include "Shock/Assert/Assert.h"
#include "Shock/Platform/Memory.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Pattern {

// ---------------------------------------------------------------

template < typename T >
Shock::Thread::Mutex	Singleton< T >::s_kMutex;

template < typename T >
T*						Singleton< T >::s_pInstance( 0 );

template < typename T >
Shock::Types::size_t	Singleton< T >::s_iReferenceCount( 0 );

// ---------------------------------------------------------------

template < typename T >
Singleton< T >::Singleton()
{
};

// ---------------------------------------------------------------

template < typename T >
Singleton< T >::~Singleton()
{
	SHOCK_ASSERT( 0 == s_iReferenceCount );
};

// ---------------------------------------------------------------

template < typename T >
T* Singleton< T >::addReference()
{
	// -->> Lock
	Shock::Thread::ScopedMutexLock kLock( s_kMutex );

	// check if the object exists
	if ( 0 == s_pInstance )
	{
		s_pInstance = new T();
	}

	// add a reference
	++s_iReferenceCount;

	return s_pInstance;
	// <<-- Release
};

// ---------------------------------------------------------------

template < typename T >
void Singleton< T >::removeReference()
{
	// validate the reference count
	SHOCK_ASSERT_EXPLODE( 0 < s_iReferenceCount );

	// -->> Lock
	Shock::Thread::ScopedMutexLock kLock( s_kMutex );

	// decrement our reference count
	if ( s_iReferenceCount > 0 )
	{
		--s_iReferenceCount;

		// check if we should delete our singleton
		if ( s_iReferenceCount == 0 )
		{
			SHOCK_SAFE_DELETE( s_pInstance );
		}
	}

	// <<-- Release
};

// ---------------------------------------------------------------

template < typename T >
T* Singleton< T >::getInstance()
{
	return s_pInstance;
};

// ---------------------------------------------------------------

}; // namespace Pattern
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* SINGLETON_HXX_ */
