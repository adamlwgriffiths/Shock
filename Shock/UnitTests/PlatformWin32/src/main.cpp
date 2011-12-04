/*
 * main.cpp
 *
 *  Created on: 29/06/2010
 *      Author: adam
 */

// ---------------------------------------------------------------
// CppUnit Includes
/*
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

// ---------------------------------------------------------------

int main( int argc, char* argv[] )
{
	// Create the event manager and test controller
	CPPUNIT_Shock::TestResult controller;

	// Add a listener that colllects test result
	CPPUNIT_Shock::TestResultCollector result;
	controller.addListener( &result );

	// Add a listener that print dots as test run.
	CPPUNIT_Shock::BriefTestProgressListener progress;
	controller.addListener( &progress );

	// Add the top suite to the test runner
	CPPUNIT_Shock::TestRunner runner;
	runner.addTest( CPPUNIT_Shock::TestFactoryRegistry::getRegistry().makeTest() );
	runner.run( controller );

	// Print test in a compiler compatible format.
	CPPUNIT_Shock::CompilerOutputter outputter( &result, CPPUNIT_Shock::stdCOut() );
	outputter.write();

	std::cout << "Press enter to continue..." << std::endl;
	getchar();

	return result.wasSuccessful() ? 0 : 1;
}
*/

// ---------------------------------------------------------------

#include <cstdio>
#include <iostream>
#include "Shock/Platform/Platform.h"
#include "Shock/Types/Limits.h"
#include "Shock/Endian/Endian.h"
#include "Shock/Compiler/Compiler.h"

int main( int argc, char* argv[] )
{
	std::cout
		<< "Unit Test: Shock::PlatformWin32"
		<< std::endl
		<< std::flush;

	// Platform detection
#if defined( SHOCK_PLATFORM_WINDOWS )
	std::cout
		<< "SUCCESS: SHOCK_PLATFORM_WINDOWS is defined"
		<< std::endl
		<< std::flush;
#else
	std::cout
		<< "FAILURE: SHOCK_PLATFORM_WINDOWS is defined"
		<< std::endl
		<< std::flush;
#endif

	std::cout
		<< "Shock::Platform::Family is "
		<< Shock::Platform::Family
		<< std::endl
		<< std::flush;

	std::cout
		<< "Shock::Platform::Description is "
		<< Shock::Platform::Description
		<< std::endl
		<< std::flush;

	std::cout
		<< "Shock::Platform::Bits::Description is "
		<< Shock::Platform::Bits::Description
		<< std::endl
		<< std::flush;


#if defined( SHOCK_PLATFORM_LITTLE_ENDIAN )
	std::cout
		<< "SUCCESS: SHOCK_PLATFORM_LITTLE_ENDIAN is defined"
		<< std::endl
		<< std::flush;
#elif defined( SHOCK_PLATFORM_BIG_ENDIAN )
	std::cout
		<< "FAILURE: SHOCK_PLATFORM_BIG_ENDIAN is defined"
		<< std::endl
		<< std::flush;
#else
	std::cout
		<< "FAILURE: No endian is defined"
		<< std::endl
		<< std::flush;
#endif

	std::cout
		<< "Shock::Platform::Endian::Description is "
		<< Shock::Platform::Endian::Description
		<< std::endl
		<< std::flush;

	if (
		Shock::Platform::Endian::Endian ==
			Shock::Consts::Platform::Endian::LittleEndian
		)
	{
		std::cout
			<< "Shock::Platform::Endian::Endian == Shock::Consts::Platform::Endian::LittleEndian"
			<< std::endl
			<< std::flush;
	}
	else if (
		Shock::Platform::Endian::Endian ==
			Shock::Consts::Platform::Endian::BigEndian
		)
	{
		std::cout
			<< "Shock::Platform::Endian::Endian == Shock::Consts::Platform::Endian::BigEndian"
			<< std::endl
			<< std::flush;
	}

	// Compiler
	std::cout
		<< "Shock::Compiler::Description is "
		<< Shock::Compiler::Description
		<< std::endl
		<< std::flush;

	std::cout
		<< "Shock::Compiler::Version is "
		<< Shock::Compiler::Version
		<< std::endl
		<< std::flush;


	// Types
	{
		Shock::Types::uint32_t iValue( Shock::Consts::Types::Uint32::Max );
		std::cout
			<< "Shock::uint32_t Max = "
			<< iValue
			<< std::endl
			<< std::flush;
	}

	{
		Shock::Types::uint32_t iValue( Shock::Consts::Types::Uint32::Min );
		std::cout
			<< "Shock::uint32_t Min = "
			<< iValue
			<< std::endl
			<< std::flush;
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
