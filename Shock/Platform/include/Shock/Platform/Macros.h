/*
 * MacroUtils.h
 *
 *  Created on: 20/06/2010
 *      Author: adam
 */

#ifndef MACROUTILS_H_
#define MACROUTILS_H_

// ---------------------------------------------------------------
// Macro helper functions
#define __stringize(n) #n
#define __eval(line) __stringize(line)

/*!
 * \brief Join macro.
 *
 * borrowed from: POCO_JOIN
 *
 * The following piece of macro magic joins the two
 * arguments together, even when one of the arguments is
 * itself a macro (see 16.3.1 in C++ standard).  The key
 * is that macro expansion of macro arguments does not
 * occur in POCO_DO_JOIN2 but does in POCO_DO_JOIN.
 */
#define SHOCK_JOIN(X, Y)					SHOCK_DO_JOIN(X, Y)
#define SHOCK_DO_JOIN(X, Y)				SHOCK_DO_JOIN2(X, Y)
#define SHOCK_DO_JOIN2(X, Y)			X##Y

// ---------------------------------------------------------------
// ensure NULL is defined
#ifndef NULL
#	define NULL									0
#endif

// ---------------------------------------------------------------

#endif /* MACROUTILS_H_ */
