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
// System Includes
#include <cstdio>
#include <iostream>

// Shock Includes
#include "Shock/SafeInteger/Operations.h"
#include "Shock/SafeInteger/SafeInteger.h"
#include "Shock/Types/Types.h"
#include "Shock/Types/Limits.h"
#include "Shock/Types/Conversion.h"

template class Shock::SafeInteger::Operations< Shock::Types::uint8_t >;

int main( int argc, char* argv[] )
{
	std::cout
		<< "Unit Test: Shock::SafeInteger"
		<< std::endl
		<< std::flush;

	// uint8_t
	std::cout
		<< "Uint8"
		<< std::endl
		<< std::flush;
	{
		std::cout
			<< "Valid Increment"
			<< std::endl
			<< std::flush;

		Shock::Types::uint8_t iOriginal( 5 );
		Shock::Types::uint8_t iIncrement( 1 );

		Shock::Types::ConversionError kError;

		Shock::Types::uint8_t iResult(
			Shock::SafeInteger::Operations< Shock::Types::uint8_t >::add(
				iOriginal,
				iIncrement,
				kError
				)
			);

		std::cout
			<< (size_t)iOriginal
			<< " + "
			<< (size_t)1
			<< " = "
			<< (size_t)iResult
			<< std::endl
			<< std::flush;

		if ( iResult == iOriginal + 1 )
		{
			std::cout
				<< "SUCCESS: Value changed"
				<< std::endl
				<< std::flush;
		}
		else
		{
			std::cout
				<< "FAILURE: Value did not change"
				<< std::endl
				<< std::flush;
		}

		if ( false == kError.isErrorSet() )
		{
			std::cout
				<< "SUCCESS: Error code is not set"
				<< std::endl
				<< std::flush;
		}
		else
		{
			std::cout
				<< "FAILURE: Error code is set"
				<< std::endl
				<< std::flush;
		}
	}
	{
		std::cout
			<< "Overflow"
			<< std::endl
			<< std::flush;

		Shock::Types::uint8_t iOriginal(
			Shock::Consts::Types::Uint8::Max
			);
		Shock::Types::uint8_t iIncrement(
			1
			);

		Shock::Types::ConversionError kError;

		Shock::Types::uint8_t iResult(
			Shock::SafeInteger::Operations< Shock::Types::uint8_t >::add(
				iOriginal,
				iIncrement,
				kError
				)
			);

		std::cout
			<< (size_t)iOriginal
			<< " + "
			<< (size_t)1
			<< " = "
			<< (size_t)iResult
			<< std::endl
			<< std::flush;

		if ( iOriginal == iResult )
		{
			std::cout
				<< "SUCCESS: Value did not change"
				<< std::endl
				<< std::flush;
		}
		else
		{
			std::cout
				<< "FAILURE: Value changed"
				<< std::endl
				<< std::flush;
		}

		if ( true == kError.isErrorSet() )
		{
			std::cout
				<< "SUCCESS: Error code is set"
				<< std::endl
				<< std::flush;
		}
		else
		{
			std::cout
				<< "FAILURE: Error code is not set"
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
