/*
 * PropertyContainer.cpp
 *
 *  Created on: 04/01/2011
 *      Author: adam
 */

#include "Shock/DataStore/PropertyContainer.h"

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Assert/Assert.h"

// ---------------------------------------------------------------

namespace Shock {
namespace DataStore {

// ---------------------------------------------------------------

PropertyContainer::PropertyContainer() :
	m_kPropertyList()
{
}

// ---------------------------------------------------------------

PropertyContainer::~PropertyContainer()
{
	// do nothing
}

// ---------------------------------------------------------------

PropertyContainer::PropertyList const & PropertyContainer::getProperties() const
{
	return m_kPropertyList;
}

// ---------------------------------------------------------------

Shock::DataStore::Property const * PropertyContainer::findProperty( std::string const & sName ) const
{
	Shock::DataStore::Property const * pProperty( 0 );

	PropertyList::const_iterator kPropertyIt( m_kPropertyList.begin() );
	while ( kPropertyIt != m_kPropertyList.end() )
	{
		if ( (*kPropertyIt)->getName() == sName )
		{
			pProperty = *kPropertyIt;
			break;
		}

		++kPropertyIt;
	}

	return pProperty;
}

// ---------------------------------------------------------------

void PropertyContainer::registerProperty( Shock::DataStore::Property* pProperty )
{
	SHOCK_ASSERT_EXPLODE( 0 != pProperty );

	// ensure the property isn't already registered
	SHOCK_ASSERT_EXPLODE( 0 == findProperty( pProperty->getName() ) );

	// add the property to our list
	m_kPropertyList.push_back( pProperty );
}

// ---------------------------------------------------------------

}; // namespace DataStore
}; // namespace Shock

// ---------------------------------------------------------------
