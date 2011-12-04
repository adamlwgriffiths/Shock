/*
 * Assert.h
 *
 *  Created on: 03/10/2010
 *      Author: Adam Griffiths
 */

#ifndef ASSERT_H_
#define ASSERT_H_

// ---------------------------------------------------------------

#include <assert.h>

// TODO: implement awesome assert macro
#define SHOCK_ASSERT( x )					assert( x )
#define SHOCK_ASSERT_EXPLODE( x )			assert( x )
#define SHOCK_ASSERT_EXPLODE_MSG( x, msg )	assert( x )
#define SHOCK_EXPLODE_MSG( x )				assert( x )

// ---------------------------------------------------------------
// Macros
/*
#define SMART_ASSERT_A( exp )					SMART_ASSERT_OP(exp, B)
#define SMART_ASSERT_B( exp )					SMART_ASSERT_OP(exp, A)
#define SMART_ASSERT_OP( exp, next )	\
	SMART_ASSERT_A.printCurrentValue((exp), #exp).SMART_ASSERT_ ## next

#define SMART_ASSERT( exp )				\
	do									\
	{									\
		if ( false == (exp) )			\
		{								\
			makeAssert( #exp ).printContext( __FILE__, __LINE__).SMART_ASSERT_A;	\
		}								\
	} while ( 0 )

// ---------------------------------------------------------------

namespace Shock {
namespace Assert {
*/
// ---------------------------------------------------------------
// TODO: implement http://www.drdobbs.com/cpp/184403745
// TODO: see https://www.securecoding.cert.org/confluence/display/seccode/DCL03-C.+Use+a+static+assertion+to+test+the+value+of+a+constant+expression
// for information on static asserts
// TODO: create a debugging assertion handler that triggers break points
// TODO: create a null assertion hnalder that does nothing
// TODO: create a logging assertion handler that sends a FATAL log message

/*!
 * This class uses the trick explained here
 * http://www.drdobbs.com/cpp/184403745
 */
/*
class Assert
{
	public:
	Assert();
		virtual ~Assert();

		Assert &		SMART_ASSERT_A;
		Assert &		SMART_ASSERT_B;

		Assert &		print_current_val(
			bool bExpression,
			const char* strExpression
			);
};

// ---------------------------------------------------------------

}; // namespace Assert
}; // namespace Shock
*/
// ---------------------------------------------------------------

#endif /* ASSERT_H_ */
