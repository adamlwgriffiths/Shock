/*
 * main.cpp
 *
 *  Created on: 03/01/2011
 *      Author: adam
 */

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Memory/ObjectPool.h"

// System Includes
#include <cstdio>
#include <iostream>

// ---------------------------------------------------------------

class TestObject
{
	public:
		TestObject()
		{
			std::cout
				<< "SUCCESS: object constructor called"
				<< std::endl
				<< std::flush;
		};
		~TestObject()
		{
			std::cout
				<< "SUCCESS: object destructor called"
				<< std::endl
				<< std::flush;
		};
};

// ---------------------------------------------------------------

int main( int argc, char* argv[] )
{
	std::cout
		<< "Unit Test: Shock::Memory"
		<< std::endl
		<< std::flush;

	// Object Pool
	{
		Shock::Memory::ObjectPool< TestObject > kPool( 5, 1 );

		// get our memory allocation
		void* raw = kPool.allocate();

		// manually invoke the constructor using the memory w'eve been given
		TestObject* pObject = new(raw) TestObject();

		// invoke the destructor manually
		pObject->~TestObject();

		// release the object
		kPool.release( pObject );
	}
	// new / delete operators
	// messy syntax
	{
		Shock::Memory::ObjectPool< TestObject > kPool( 5, 1 );

		// call new on the pool
		TestObject *pObject = new( kPool ) TestObject();

		// delete the object
		operator delete( pObject, kPool );
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
