/*
 * Factory.hxx
 *
 *  Created on: 22/12/2010
 *      Author: adam
 */

#ifndef FACTORY_HXX_
#define FACTORY_HXX_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Thread/ScopedMutexLock.h"
#include "Shock/Assert/Assert.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Pattern {

// ---------------------------------------------------------------

template < typename T >
Factory< T >::Factory() :
	m_kInstantiatorContainer()
{
};

// ---------------------------------------------------------------

template < typename T >
Factory< T >::Factory( Shock::Types::size_t const & iDefaultContainerSize ) :
	m_kInstantiatorContainer()
{
	// reserve enough space
	m_kInstantiatorContainer.reserve( iDefaultContainerSize );
};

// ---------------------------------------------------------------

template < typename T >
Factory< T >::~Factory()
{
	// ensure we don't have any instantiators left
	SHOCK_ASSERT( 0 == m_kInstantiatorContainer.size() );
};

// ---------------------------------------------------------------

template < typename T >
void Factory< T >::addInstantiator( Shock::Pattern::Instantiator< T > * pInstantiator )
{
	SHOCK_ASSERT_EXPLODE( 0 != pInstantiator );
	SHOCK_ASSERT( 0 == findInstantiator( pInstantiator->getObjectType() ) );

	m_kInstantiatorContainer.push_back( pInstantiator );
};

// ---------------------------------------------------------------

template < typename T >
void Factory< T >::removeInstantiator( Shock::Pattern::Instantiator< T > * pInstantiator )
{
	SHOCK_ASSERT_EXPLODE( 0 != pInstantiator );
	bool bFound( false );

	typename InstantiatorContainer::iterator kIt( m_kInstantiatorContainer.begin() );
	while ( kIt != m_kInstantiatorContainer.end() )
	{
		if ( *kIt == pInstantiator )
		{
			m_kInstantiatorContainer.erase( kIt );
			bFound = true;
			break;
		}
		++kIt;
	}
	SHOCK_ASSERT( true == bFound );
};

// ---------------------------------------------------------------

template < typename T >
T* Factory< T >::create( std::string const & sObjectType )
{
	T* pInstance( 0 );

	Shock::Pattern::Instantiator< T >* pInstantiator(
		findInstantiator( sObjectType )
		);

	// TODO: log a warning if the object type doesn't exist
	if ( 0 != pInstantiator )
	{
		pInstance = pInstantiator->create();
	}

	return pInstance;
};

// ---------------------------------------------------------------

template < typename T >
void Factory< T >::destroy( std::string const & sObjectType, T* pObject )
{
	Shock::Pattern::Instantiator< T >* pInstantiator(
		findInstantiator( sObjectType )
		);

	// ensure the instantiator exists
	SHOCK_ASSERT( 0 != pInstantiator );

	if ( 0 != pInstantiator )
	{
		pInstantiator->destroy( pObject );
	}
};

// ---------------------------------------------------------------

template < typename T >
Shock::Pattern::Instantiator< T >* Factory< T >::findInstantiator( std::string const & sObjectType )
{
	Shock::Pattern::Instantiator< T >* pInstantiator( 0 );

	typename InstantiatorContainer::iterator kIt( m_kInstantiatorContainer.begin() );
	while ( kIt != m_kInstantiatorContainer.end() )
	{
		if ( (*kIt)->getObjectType() == sObjectType )
		{
			pInstantiator = *kIt;
			break;
		}
		++kIt;
	}

	return pInstantiator;
};

// ---------------------------------------------------------------

}; // namespace Pattern
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* FACTORY_HXX_ */
