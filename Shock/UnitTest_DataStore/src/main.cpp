/*
 * main.cpp
 *
 *  Created on: 03/01/2011
 *      Author: adam
 */

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/DataStore/DataContainer.h"
#include "Shock/DataStore/Property.h"

// System Includes
#include <cstdio>
#include <iostream>

namespace {
std::string const		g_sPropertyName( "MyInt" );
Shock::Types::int32_t	g_iPropertyValue( 10 );
};

// ---------------------------------------------------------------

class TestDataContainer :
	public Shock::DataStore::DataContainer
{
	public:
		TestDataContainer() :
			DataContainer( "MyDataContainer" ),
			m_kIntProperty(
				g_sPropertyName,
				Shock::DataStore::Property::Int32
				)
		{
			registerProperty( &m_kIntProperty );
			m_kIntProperty.setInt32( g_iPropertyValue );
		};
		~TestDataContainer()
		{
		};
	private:
		Shock::DataStore::Property		m_kIntProperty;
};

// ---------------------------------------------------------------

int main( int argc, char* argv[] )
{
	std::cout
		<< "Unit Test: Shock::DataStore"
		<< std::endl
		<< std::flush;

	// Test DataContainer
	{
		TestDataContainer kDataContainer;
		Shock::DataStore::Property const * pProperty(
			kDataContainer.findProperty( g_sPropertyName )
			);
		if ( 0 != pProperty )
		{
			std::cout
				<< "SUCCESS: Property found"
				<< std::endl
				<< std::flush;

			if ( pProperty->getInt32() == g_iPropertyValue )
			{
				std::cout
					<< "SUCCESS: Property has value of '"
					<< g_iPropertyValue
					<< "'"
					<< std::endl
					<< std::flush;
			}
			else
			{
				std::cout
					<< "FAILURE: Property has value of '"
					<< g_iPropertyValue
					<< "'"
					<< std::endl
					<< std::flush;
			}
		}
		else
		{
			// failure
			std::cout
				<< "FAILURE: Property not found"
				<< std::endl
				<< std::flush;
		}
	}

	// Complete
	std::cout
		<< "Press enter to continue..."
		<< std::endl
		<< std::flush;
	getchar();

	return 0;
}

// ---------------------------------------------------------------
