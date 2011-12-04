/*
 * ObjectPoolBlock.hxx
 *
 *  Created on: 02/01/2011
 *      Author: adam
 */

#ifndef OBJECTPOOLBLOCK_HXX_
#define OBJECTPOOLBLOCK_HXX_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Assert/Assert.h"

// Standard Includes
#include <new>		// std::bad_alloc
#include <cstdlib>	// malloc
#include <cstring>	// memset

// ---------------------------------------------------------------

namespace Shock {
namespace Memory {

// ---------------------------------------------------------------

template < typename T >
ObjectPoolBlock< T >::ObjectPoolBlock(
	Shock::Types::size_t const & iAllocationSize
	) :
	m_pMemory( 0 ),
	m_iAllocationSize( iAllocationSize ),
	m_kUnallocatedObjects(),
	m_kAllocatedObjects()
{
	// TODO: replace any memory allocation with safe integer / safe allocation calls
	SHOCK_ASSERT_EXPLODE( 0 < m_iAllocationSize );
	m_pMemory = (Shock::Types::uint8_t*)malloc( m_iAllocationSize * sizeof( T ) );
	if ( 0 == m_pMemory )
	{
		// TODO: throw an exception
		throw std::bad_alloc();
	}

	// write debug memory over the pool
	memset( m_pMemory, 0xDEADBEEF, m_iAllocationSize * sizeof( T ) );

	// TODO: optimise this horrid logic
	// this is very un-optimised
	// but for the sake of getting up and running, it's here
	//
	// add our un-allocated objects to the un-allocated pool
	for (
		Shock::Types::size_t iIndex( 0 );
		iIndex < m_iAllocationSize;
		++iIndex
		)
	{
		m_kUnallocatedObjects.insert( (Shock::Types::uint8_t*)m_pMemory + (iIndex * sizeof( T )) );
	}
};

// ---------------------------------------------------------------

template < typename T >
ObjectPoolBlock< T >::~ObjectPoolBlock()
{
	// TODO: convert this to a log error
	SHOCK_ASSERT_EXPLODE( 0 == m_kAllocatedObjects.size() );

	// free our memory
	free( (void*)m_pMemory );
	m_pMemory = 0;
};

// ---------------------------------------------------------------

template < typename T >
void* ObjectPoolBlock< T >::allocate()
{
	// check we have a free object
	SHOCK_ASSERT_EXPLODE( 0 < m_kUnallocatedObjects.size() );

	// get the first un-allocated object
	typename AllocationList::iterator kIterator( m_kUnallocatedObjects.begin() );

	void* pPtr( *kIterator );

	// ensure it isn't already allocated
	SHOCK_ASSERT_EXPLODE( m_kAllocatedObjects.find( pPtr ) == m_kAllocatedObjects.end() );

	// remove from our un-allocated object list
	m_kUnallocatedObjects.erase( kIterator );

	// add to our allocated object list
	m_kAllocatedObjects.insert( pPtr );

	return (void*)pPtr;
};

// ---------------------------------------------------------------

template < typename T >
void ObjectPoolBlock< T >::release( void* pPtr )
{
	// check the pointer is valid
	SHOCK_ASSERT_EXPLODE( m_pMemory <= pPtr );
	SHOCK_ASSERT_EXPLODE( m_pMemory + (m_iAllocationSize * sizeof( T )) > pPtr );

	// ensure it is in the list
	SHOCK_ASSERT_EXPLODE( m_kUnallocatedObjects.find( pPtr ) == m_kUnallocatedObjects.end() );

	// find the object in our list
	typename AllocationList::iterator kIterator( m_kAllocatedObjects.find( pPtr ) );
	SHOCK_ASSERT_EXPLODE( kIterator != m_kAllocatedObjects.end() );

	// remove from our allocated object list
	m_kAllocatedObjects.erase( kIterator );

	// add to our un-allocated object list
	m_kUnallocatedObjects.insert( pPtr );
};

// ---------------------------------------------------------------

template < typename T >
Shock::Types::size_t ObjectPoolBlock< T >::getAllocationsRemaining() const
{
	return m_kUnallocatedObjects.size();
};

// ---------------------------------------------------------------

}; // namespace Memory
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* OBJECTPOOLBLOCK_HXX_ */
