#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

// ---------------------------------------------------------------
// Core Includes
#include "AWE/Core/Core.h"

// Network Includes
#include "AWE/Ping/Ping.h"

// ---------------------------------------------------------------

int main( int argc, char* argv[] )
{
	AWE::Core::init();
	AWE::Socket::init();

	// Create the event manager and test controller
	CPPUNIT_NS::TestResult controller;

	// Add a listener that colllects test result
	CPPUNIT_NS::TestResultCollector result;
	controller.addListener( &result );        

	// Add a listener that print dots as test run.
	CPPUNIT_NS::BriefTestProgressListener progress;
	controller.addListener( &progress );      

	// Add the top suite to the test runner
	CPPUNIT_NS::TestRunner runner;
	runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
	runner.run( controller );

	// Print test in a compiler compatible format.
	CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
	outputter.write();

	AWE::Socket::shutdown();
	AWE::Core::shutdown();

	std::cout << "Press enter to continue..." << std::endl;
	getchar();

	return result.wasSuccessful() ? 0 : 1;
}

// ---------------------------------------------------------------