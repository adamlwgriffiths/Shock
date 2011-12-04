/*
 * Singleton.h
 *
 *  Created on: 31/10/2010
 *      Author: adam
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Thread/Mutex.h"
#include "Shock/Types/Types.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Pattern {

// ---------------------------------------------------------------

template < typename T >
class Singleton
{
	public:
		static T*			addReference();
		static void			removeReference();

		static T*			getInstance();

	protected:
		Singleton();
		virtual ~Singleton();

	private:
		// No copying
		// No implementation provided
		Singleton( Singleton const & kOther );
		Singleton< T >&		operator=( Singleton< T > const & kOther );

	protected:
		static Shock::Thread::Mutex	s_kMutex;
		static T*			s_pInstance;
		static Shock::Types::size_t	s_iReferenceCount;
};

// ---------------------------------------------------------------

}; // namespace Pattern
}; // namespace Shock

// ---------------------------------------------------------------

// include our template implementation
#include "Shock/Pattern/Singleton.hxx"

// ---------------------------------------------------------------

#endif /* SINGLETON_H_ */
