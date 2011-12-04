/*
 * ObjectPool.hxx
 *
 *  Created on: 02/01/2011
 *      Author: adam
 */

#ifndef OBJECTPOOL_HXX_
#define OBJECTPOOL_HXX_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Assert/Assert.h"
#include "Shock/Types/Types.h"
#include "Shock/Platform/Memory.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Memory {

// ---------------------------------------------------------------

template < typename T >
ObjectPool< T >::ObjectPool(
	Shock::Types::size_t const & iBlockAllocationSize,
	Shock::Types::size_t const & iInitiallyAllocatedBlocks,
	Shock::Types::uint8_t const & iMinimumFreePercentage
	) :
	m_iBlockAllocationSize( iBlockAllocationSize ),
	m_iBlocksAllocated( 0 ),
	m_kFullBlocks(),
	m_kNonFullBlocks(),
	m_kAllocationMappings(),
	m_iMaxAllocations( 0 ),
	m_iCurrentAllocations( 0 ),
	m_iAllocationHighWaterMark( 0 ),
	m_iMinimumFreePercentage( iMinimumFreePercentage )
{
	// allocate our blocks
	while ( m_iBlocksAllocated < iInitiallyAllocatedBlocks )
	{
		allocateBlock();
	}
}

// ---------------------------------------------------------------

template < typename T >
ObjectPool< T >::~ObjectPool()
{
	// free our blocks
	// delete our non full blocks
	typename PoolContainer::iterator kBlockIterator( m_kNonFullBlocks.begin() );
	while ( m_kNonFullBlocks.end() != kBlockIterator )
	{
		ObjectPoolBlock< T >* pPool( *kBlockIterator );
		SHOCK_SAFE_DELETE( pPool );
		++kBlockIterator;
	}

	// delete our full blocks
	kBlockIterator = m_kFullBlocks.begin();
	while ( m_kFullBlocks.end() != kBlockIterator )
	{
		ObjectPoolBlock< T >* pPool( *kBlockIterator );
		SHOCK_SAFE_DELETE( pPool );
		++kBlockIterator;
	}
}

// ---------------------------------------------------------------

template < typename T >
void* ObjectPool< T >::allocate()
{
	// ensure we actually have a valid block
	if ( 0 == m_kNonFullBlocks.size() )
	{
		allocateBlock();
	}

	// find a memory block with free allocations
	typename PoolContainer::iterator kNonFullBlockIterator( m_kNonFullBlocks.begin() );
	SHOCK_ASSERT_EXPLODE( m_kNonFullBlocks.end() != kNonFullBlockIterator );

	// allocate an item
	ObjectPoolBlock< T >* pBlock = *kNonFullBlockIterator;
	void* pPtr( pBlock->allocate() );

	// add the pointer to our memory mapping
	m_kAllocationMappings.insert(
		std::pair< void*, ObjectPoolBlock< T >* >( pPtr, pBlock )
		);

	// increment our number of allocations
	++m_iCurrentAllocations;

	// check if we've reached a high-water mark
	if ( m_iCurrentAllocations > m_iAllocationHighWaterMark )
	{
		// update our high water mark
		m_iAllocationHighWaterMark = m_iCurrentAllocations;
	}

	// check if the memory block is now full
	if ( 0 >= pBlock->getAllocationsRemaining() )
	{
		// remove from our non-full block list
		m_kNonFullBlocks.erase( kNonFullBlockIterator );

		// add to our full block list
		m_kFullBlocks.insert( pBlock );
	}

	// allocate enough memory to drop us below the minimum free percentage
	// theshold
	while ( getPercentageAllocated() > m_iMinimumFreePercentage )
	{
		allocateBlock();
	}

	return pPtr;
}

// ---------------------------------------------------------------

template < typename T >
void ObjectPool< T >::release( void* pPtr )
{
	// find the pointer in our allocation mappings
	typename AllocationMapping::iterator kMappingIterator( m_kAllocationMappings.find( pPtr ) );
	SHOCK_ASSERT_EXPLODE( m_kAllocationMappings.end() != kMappingIterator );

	// find the block the pointer came from
	ObjectPoolBlock< T >* pBlock = kMappingIterator->second;
	SHOCK_ASSERT_EXPLODE( 0 != pBlock );

	// check if the block was previously full
	if ( 0 == pBlock->getAllocationsRemaining() )
	{
		// move the block to our un-full list
		typename PoolContainer::iterator kFullBlockIterator( m_kFullBlocks.find( pBlock ) );
		m_kFullBlocks.erase( kFullBlockIterator );

		// add to our full block list
		m_kNonFullBlocks.insert( pBlock );
	}

	// release the pointer
	pBlock->release( pPtr );

	// remove it from the allocation mapping list
	m_kAllocationMappings.erase( kMappingIterator );

	// decrement our current allocations
	SHOCK_ASSERT_EXPLODE( 0 < m_iCurrentAllocations );
	--m_iCurrentAllocations;
}

// ---------------------------------------------------------------

template < typename T >
void ObjectPool< T >::allocateBlock()
{
	// create our memory block
	ObjectPoolBlock< T >* pBlock = new ObjectPoolBlock< T >( m_iBlockAllocationSize );

	// add it to our pool
	m_kNonFullBlocks.insert( pBlock );

	// increment the number of blocks
	++m_iBlocksAllocated;

	// increase our max allocations size
	m_iMaxAllocations += m_iBlockAllocationSize;
}

// ---------------------------------------------------------------

template < typename T >
Shock::Types::size_t const & ObjectPool< T >::getBlockAllocationSize() const
{
	return m_iBlockAllocationSize;
}

// ---------------------------------------------------------------

template < typename T >
Shock::Types::size_t const & ObjectPool< T >::getBlocksAllocated() const
{
	return m_iBlocksAllocated;
}

// ---------------------------------------------------------------

template < typename T >
Shock::Types::size_t const & ObjectPool< T >::getTotalSize() const
{
	return m_iBlocksAllocated;
}

// ---------------------------------------------------------------

template < typename T >
Shock::Types::size_t const & ObjectPool< T >::getAllocations() const
{
	return m_iCurrentAllocations;
}

// ---------------------------------------------------------------

template < typename T >
Shock::Types::size_t const & ObjectPool< T >::getAllocationHighWaterMark() const
{
	return m_iAllocationHighWaterMark;
}

// ---------------------------------------------------------------

template < typename T >
Shock::Types::uint8_t ObjectPool< T >::getPercentageAllocated() const
{
	return
		(Shock::Types::uint8_t)(
			((Shock::Types::size_t)m_iCurrentAllocations * 100) / m_iMaxAllocations
			);
}

// ---------------------------------------------------------------

}; // namespace Memory
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* OBJECTPOOL_HXX_ */
