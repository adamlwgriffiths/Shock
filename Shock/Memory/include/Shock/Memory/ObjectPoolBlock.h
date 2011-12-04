/*
 * ObjectPoolBlock.h
 *
 *  Created on: 02/01/2011
 *      Author: adam
 */

#ifndef OBJECTPOOLBLOCK_H_
#define OBJECTPOOLBLOCK_H_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Types/Types.h"

// Standard Includes
#include <set>

// ---------------------------------------------------------------

namespace Shock {
namespace Memory {

// ---------------------------------------------------------------
// http://www.parashift.com/c++-faq-lite/dtors.html#faq-11.14
// TODO: optimise this class
// TODO: add debugging padding with canaries
// TODO: add checks when allocating/releasing a memory object that no over-writes occured
template < typename T >
class ObjectPoolBlock
{
	public:
		explicit ObjectPoolBlock( Shock::Types::size_t const & iAllocationSize );
		~ObjectPoolBlock();

		void*				allocate();
		void				release( void* pPtr );

		Shock::Types::size_t	getAllocationsRemaining() const;

	private:
		typedef std::set< void* >	AllocationList;

		Shock::Types::uint8_t*		m_pMemory;
		Shock::Types::size_t const	m_iAllocationSize;
		AllocationList				m_kUnallocatedObjects;
		AllocationList				m_kAllocatedObjects;
};

// ---------------------------------------------------------------

}; // namespace Memory
}; // namespace Shock

// ---------------------------------------------------------------

// include our template implementation
#include "Shock/Memory/ObjectPoolBlock.hxx"

// ---------------------------------------------------------------

#endif /* OBJECTPOOLBLOCK_H_ */
