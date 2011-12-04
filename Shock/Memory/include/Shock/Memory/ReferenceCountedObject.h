/*
 * ReferenceCountedObject.h
 *
 *  Created on: 16/12/2010
 *      Author: adam
 */

#ifndef REFERENCECOUNTEDOBJECT_H_
#define REFERENCECOUNTEDOBJECT_H_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Types/Limits.h"
#include "Shock/Thread/Mutex.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Memory {

// ---------------------------------------------------------------

/*!
 * /brief Implements the weighted reference counting algorithm
 *
 * http://en.wikipedia.org/wiki/Reference_counting#Weighted_reference_counting
 */
template < typename T >
class ReferenceCountedObject
{
	public:
		ReferenceCountedObject( T* pObject );
		ReferenceCountedObject( ReferenceCountedObject< T > & kOther );
		virtual ~ReferenceCountedObject();

		T*				getPointer();
		void			clearPointer();

		T*				operator->();
		T&				operator*();
		ReferenceCountedObject< T >&	operator=( ReferenceCountedObject< T > & kOther );

	private:
		class SharedObject
		{
			public:
				SharedObject( T* pObject );
				~SharedObject();

				Shock::Types::size_t	releaseWeight( Shock::Types::size_t const & iWeight );
				Shock::Types::size_t	divideWeight();

				T*		m_pObject;
				Shock::Types::size_t	m_iReleasedWeight;
				Shock::Thread::Mutex	m_kMutex;
		};

		Shock::Types::size_t	divideWeight();
		void					releaseWeight();

		SharedObject				*m_pSharedObject;
		Shock::Types::size_t		m_iWeight;
		Shock::Thread::Mutex		m_kMutex;
};

// ---------------------------------------------------------------

}; // namespace Memory
}; // namespace Shock

// ---------------------------------------------------------------

// include our template implementation
#include "Shock/Memory/ReferenceCountedObject.hxx"

// ---------------------------------------------------------------

#endif /* REFERENCECOUNTEDOBJECT_H_ */
