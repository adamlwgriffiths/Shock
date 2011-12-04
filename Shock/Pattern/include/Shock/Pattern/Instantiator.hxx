/*
 * Instantiator.hxx
 *
 *  Created on: 22/12/2010
 *      Author: adam
 */

#ifndef INSTANTIATOR_HXX_
#define INSTANTIATOR_HXX_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Assert/Assert.h"
#include "Shock/Platform/Memory.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Pattern {

// ---------------------------------------------------------------

template < typename T >
Instantiator< T >::Instantiator( char const * sObjectType ) :
	m_sObjectType( sObjectType )
{
};

// ---------------------------------------------------------------

template < typename T >
Instantiator< T >::Instantiator( std::string const & sObjectType ) :
	m_sObjectType( sObjectType )
{
};

// ---------------------------------------------------------------

template < typename T >
Instantiator< T >::~Instantiator()
{
};

// ---------------------------------------------------------------

template < typename T >
void Instantiator< T >::destroy( T* pObject ) const
{
	SHOCK_SAFE_DELETE( pObject );
};

// ---------------------------------------------------------------

template < typename T >
std::string const &	Instantiator< T >::getObjectType() const
{
	return m_sObjectType;
};

// ---------------------------------------------------------------

}; // namespace Pattern
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* INSTANTIATOR_HXX_ */
