/*
 * ReferenceCountedObject.hxx
 *
 *  Created on: 16/12/2010
 *      Author: adam
 */

#ifndef REFERENCECOUNTEDOBJECT_HXX_
#define REFERENCECOUNTEDOBJECT_HXX_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Thread/ScopedMutexLock.h"
#include "Shock/Assert/Assert.h"
#include "Shock/Platform/Macros.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Memory {

// ---------------------------------------------------------------

template < typename T >
ReferenceCountedObject< T >::ReferenceCountedObject( T* pObject ) :
	m_pSharedObject( 0 ),
	m_iWeight( 0 ),
	m_kMutex()
{
	// check if we received a valid pointer
	if ( 0 != pObject )
	{
		m_pSharedObject = new SharedObject( pObject );
		m_iWeight = Shock::Consts::Types::Size::Max;
	}
};

// ---------------------------------------------------------------

template < typename T >
ReferenceCountedObject< T >::ReferenceCountedObject(
	ReferenceCountedObject< T > & kOther
	) :
	m_pSharedObject( kOther.m_pSharedObject ),
	m_iWeight( kOther.divideWeight() ),
	m_kMutex()
{
};

// ---------------------------------------------------------------

template < typename T >
ReferenceCountedObject< T >::~ReferenceCountedObject()
{
	// release any weight we have
	releaseWeight();
}

// ---------------------------------------------------------------

template < typename T >
T* ReferenceCountedObject< T >::getPointer()
{
	T* pObject( 0 );
	if ( 0 != m_pSharedObject )
	{
		pObject = m_pSharedObject->m_pObject;
	}
	return pObject;
}

// ---------------------------------------------------------------

template < typename T >
void ReferenceCountedObject< T >::clearPointer()
{
	releaseWeight();
}

// ---------------------------------------------------------------

template < typename T >
T* ReferenceCountedObject< T >::operator->()
{
	return getPointer();
}

// ---------------------------------------------------------------

template < typename T >
T& ReferenceCountedObject< T >::operator*()
{
	SHOCK_ASSERT_EXPLODE_MSG(
		0 != m_pSharedObject,
		"Attempted to dereference a null ReferenceCountedObject"
		);
	return *m_pSharedObject->m_pObject;
}

// ---------------------------------------------------------------

template < typename T >
ReferenceCountedObject< T >& ReferenceCountedObject< T >::operator=(
	ReferenceCountedObject< T > & kOther
	)
{
	// -->> Lock
	Shock::Thread::ScopedMutexLock kLock( m_kMutex );

	// release our current object
	releaseWeight();

	// acquire our new object
	m_pSharedObject = kOther.m_pSharedObject;
	m_iWeight = kOther.divideWeight();

	return *this;
	// <<-- Unlock
}

// ---------------------------------------------------------------

template < typename T >
Shock::Types::size_t ReferenceCountedObject< T >::divideWeight()
{
	// -->> Lock
	Shock::Thread::ScopedMutexLock kLock( m_kMutex );

	Shock::Types::size_t iWeight( 0 );

	if ( 0 != m_pSharedObject )
	{
		// check if we have any weight to share
		if ( 1 >= m_iWeight )
		{
			// not enough weight
			// check the root object
			// we should only do this sparingly
			iWeight = m_pSharedObject->divideWeight();

			if ( 0 >= iWeight )
			{
				// too many references
				SHOCK_EXPLODE_MSG( "Too many references to ReferenceCountedObject" );
			}
		}
		else
		{
			// divide our weight in half
			iWeight = m_iWeight / 2;

			// ensure we don't get rounding errors
			if ( m_iWeight != (iWeight * 2) )
			{
				++iWeight;
			}

			// remove the weight form our released amount
			m_iWeight -= iWeight;
		}
	}

	return iWeight;
	// <<-- Unlock
}

// ---------------------------------------------------------------

template < typename T >
void ReferenceCountedObject< T >::releaseWeight()
{
	// -->> Lock
	Shock::Thread::ScopedMutexLock kLock( m_kMutex );

	if ( 0 != m_pSharedObject )
	{
		// release our weight back to the root object
		Shock::Types::size_t iReleasedWeight(
			m_pSharedObject->releaseWeight( m_iWeight )
			);

		// check if the full amount has been returned
		if ( Shock::Consts::Types::Size::Max == iReleasedWeight )
		{
			// free our object
			SHOCK_SAFE_DELETE( m_pSharedObject );
		}

		// clear our pointer
		m_pSharedObject = 0;
	}
	// <<-- Unlock
}

// ---------------------------------------------------------------

template < typename T >
ReferenceCountedObject< T >::SharedObject::SharedObject( T* pObject ) :
	m_pObject( pObject ),
	m_iReleasedWeight( 0 ),
	m_kMutex()
{
}

// ---------------------------------------------------------------

template < typename T >
ReferenceCountedObject< T >::SharedObject::~SharedObject()
{
	SHOCK_ASSERT( Shock::Consts::Types::Size::Max == m_iReleasedWeight );

	SHOCK_SAFE_DELETE( m_pObject );
}

// ---------------------------------------------------------------

template < typename T >
Shock::Types::size_t ReferenceCountedObject< T >::SharedObject::releaseWeight(
	Shock::Types::size_t const & iWeight
	)
{
	// -->> Lock
	Shock::Thread::ScopedMutexLock kLock( m_kMutex );

	m_iReleasedWeight += iWeight;

	return m_iReleasedWeight;
	// <<-- Unlock
}

// ---------------------------------------------------------------

template < typename T >
Shock::Types::size_t ReferenceCountedObject< T >::SharedObject::divideWeight()
{
	// -->> Lock
	Shock::Thread::ScopedMutexLock kLock( m_kMutex );

	Shock::Types::size_t iWeight( 0 );

	// check if we have any weight to share
	if ( 1 >= m_iReleasedWeight )
	{
		// too many references
		SHOCK_EXPLODE_MSG( "Too many references to ReferenceCountedObject" );
	}

	// divide our weight in half
	iWeight = m_iReleasedWeight / 2;

	// ensure we don't get rounding errors
	if ( m_iReleasedWeight != (iWeight * 2) )
	{
		++iWeight;
	}

	// remove the weight form our released amount
	m_iReleasedWeight -= iWeight;

	return iWeight;
	// <<-- Unlock
}

// ---------------------------------------------------------------

}; // namespace Memory
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* REFERENCECOUNTEDOBJECT_HXX_ */
