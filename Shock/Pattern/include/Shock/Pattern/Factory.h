/*
 * Factory.h
 *
 *  Created on: 22/12/2010
 *      Author: adam
 */

#ifndef FACTORY_H_
#define FACTORY_H_

// ---------------------------------------------------------------
// Standard Includes
#include <vector>
#include <string>

// Shock Includes
#include "Shock/Types/Types.h"
#include "Shock/Pattern/Instantiator.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Pattern {

// ---------------------------------------------------------------
// TODO: replace the vector with a tr1 unordered_map
template < typename T >
class Factory
{
	public:
		Factory();
		Factory( Shock::Types::size_t const & iDefaultContainerSize );
		virtual ~Factory();

		void				addInstantiator( Shock::Pattern::Instantiator< T > * pInstantiator );
		void				removeInstantiator( Shock::Pattern::Instantiator< T > * pInstantiator );

		virtual T*			create( std::string const & sObjectType );
		virtual void		destroy( std::string const & sObjectType, T* pObject );

	private:
		Shock::Pattern::Instantiator< T >*	findInstantiator( std::string const & sObjectType );

		typedef std::vector< Shock::Pattern::Instantiator< T > * >	InstantiatorContainer;
		InstantiatorContainer		m_kInstantiatorContainer;
};

// ---------------------------------------------------------------

}; // namespace Pattern
}; // namespace Shock

// ---------------------------------------------------------------

// include our template implementation
#include "Shock/Pattern/Factory.hxx"

// ---------------------------------------------------------------

#endif /* FACTORY_H_ */
