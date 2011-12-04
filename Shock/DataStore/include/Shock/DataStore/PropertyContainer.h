/*
 * PropertyContainer.h
 *
 *  Created on: 02/01/2011
 *      Author: adam
 */

#ifndef PROPERTYCONTAINER_H_
#define PROPERTYCONTAINER_H_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/DataStore/Property.h"

// Standard Includes
#include <vector>

// ---------------------------------------------------------------

namespace Shock {
namespace DataStore {

// ---------------------------------------------------------------

class PropertyContainer
{
	public:
		typedef std::vector< Shock::DataStore::Property* >		PropertyList;

		virtual ~PropertyContainer();

		PropertyList const &	getProperties() const;
		Shock::DataStore::Property const *	findProperty( std::string const & sName ) const;

		// virtual void		serialiseNetwork( Shock::Types::Array< uint8_t > ) = 0;
		// virtual void		serialiseHost( Shock::Types::Array< uint8_t > ) = 0;
		// virtual void		deserialiseNetwork( Shock::Types::Array< uint8_t > ) = 0;
		// virtual void		deserialiseHost( Shock::Types::Array< uint8_t > ) = 0;

	protected:
		PropertyContainer();

		void					registerProperty( Shock::DataStore::Property* pProperty );

		PropertyList			m_kPropertyList;
};

// ---------------------------------------------------------------

}; // namespace DataStore
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* PROPERTYCONTAINER_H_ */
