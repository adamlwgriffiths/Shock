/*
 * ObjectPool.h
 *
 *  Created on: 02/01/2011
 *      Author: adam
 */

#ifndef OBJECTPOOL_H_
#define OBJECTPOOL_H_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Types/Types.h"
#include "Shock/Memory/ObjectPoolBlock.h"

// Standard Includes
#include <set>
#include <map>

// ---------------------------------------------------------------

namespace Shock {
namespace Memory {

// ---------------------------------------------------------------

// http://www.parashift.com/c++-faq-lite/dtors.html#faq-11.14
// TODO: optimise this - use memory alignment
template < typename T >
class ObjectPool
{
	public:
		explicit ObjectPool(
			Shock::Types::size_t const & iBlockAllocationSize,
			Shock::Types::size_t const & iInitiallyAllocatedBlocks,
			Shock::Types::uint8_t const & iMinimumFreePercentage = 75
			);
		~ObjectPool();

		void*				allocate();
		void				release( void* pPtr );

		Shock::Types::size_t const &	getBlockAllocationSize() const;
		Shock::Types::size_t const &	getBlocksAllocated() const;
		Shock::Types::size_t const &	getTotalSize() const;
		Shock::Types::size_t const &	getAllocations() const;
		Shock::Types::size_t const &	getAllocationHighWaterMark() const;
		Shock::Types::uint8_t			getPercentageAllocated() const;

	private:
		void				allocateBlock();

		typedef std::set< ObjectPoolBlock< T >* >	PoolContainer;
		typedef std::map< void*, ObjectPoolBlock< T >* >	AllocationMapping;

		Shock::Types::size_t const	m_iBlockAllocationSize;
		Shock::Types::size_t		m_iBlocksAllocated;
		PoolContainer				m_kFullBlocks;
		PoolContainer				m_kNonFullBlocks;
		AllocationMapping			m_kAllocationMappings;
		Shock::Types::size_t		m_iMaxAllocations;
		Shock::Types::size_t		m_iCurrentAllocations;
		Shock::Types::size_t		m_iAllocationHighWaterMark;
		Shock::Types::uint8_t		m_iMinimumFreePercentage;
};

// ---------------------------------------------------------------

}; // namespace Memory
}; // namespace Shock

// ---------------------------------------------------------------

template < typename T >
inline void* operator new( size_t iBytes, Shock::Memory::ObjectPool< T > & kPool )
{
	// allocate the memory and return the pointer
	return kPool.allocate();
};

// ---------------------------------------------------------------

template < typename T >
inline void operator delete( void* pPtr, Shock::Memory::ObjectPool< T > & kPool )
{
	// manually invoke the destructor
	T* pObject( (T*)pPtr );
	pObject->~T();

	kPool.release( pPtr );
};

// ---------------------------------------------------------------

// include our template implementation
#include "Shock/Memory/ObjectPool.hxx"

// ---------------------------------------------------------------

#endif /* OBJECTPOOL_H_ */
