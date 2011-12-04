/*
 * CompilerOptions.h
 *
 *  Created on: 20/06/2010
 *      Author: adam
 */

#ifndef COMPILEROPTIOSHOCK_H_
#define COMPILEROPTIOSHOCK_H_

// ---------------------------------------------------------------

/*!
 * \brief Disable various warnings
 */
//@{
// inherits via dominance
#pragma warning (disable: 4250)
//@}

// ---------------------------------------------------------------

/*!
 * \brief Define the template AWE_TEMPLATE_EXPORT function as blank
 */
//@{
//#if !defined( SHOCK_TEMPLATE_EXPORT )
//#	define SHOCK_TEMPLATE_EXPORT				/* nothing */
//#endif
//@}

// ---------------------------------------------------------------

#endif /* COMPILEROPTIOSHOCK_H_ */
