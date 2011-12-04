/*
 * Error.hxx
 *
 *  Created on: 05/01/2011
 *      Author: adam
 */

#ifndef ERROR_HXX_
#define ERROR_HXX_

// ---------------------------------------------------------------

namespace Shock {
namespace Error {

// ---------------------------------------------------------------

template< typename ErrorType, int DefaultErrorValue >
Error< ErrorType, DefaultErrorValue >::Error() :
	m_eErrorCode( (ErrorType)DefaultErrorValue )
{
}

// ---------------------------------------------------------------

template< typename ErrorType, int DefaultErrorValue >
Error< ErrorType, DefaultErrorValue >::Error(ErrorType const & eErrorCode) :
	m_eErrorCode( eErrorCode )
{
}

// ---------------------------------------------------------------

template< typename ErrorType, int DefaultErrorValue >
Error< ErrorType, DefaultErrorValue >::~Error()
{
}

// ---------------------------------------------------------------

template< typename ErrorType, int DefaultErrorValue >
void Error< ErrorType, DefaultErrorValue >::clear()
{
	m_eErrorCode = (ErrorType)DefaultErrorValue;
}

// ---------------------------------------------------------------

template< typename ErrorType, int DefaultErrorValue >
Error< ErrorType, DefaultErrorValue > & Error< ErrorType, DefaultErrorValue >::setError(
		ErrorType const & eErrorCode
		)
{
	m_eErrorCode = eErrorCode;
	return *this;
}

// ---------------------------------------------------------------

template< typename ErrorType, int DefaultErrorValue >
ErrorType const & Error< ErrorType, DefaultErrorValue >::getError() const
{
	return m_eErrorCode;
}

// ---------------------------------------------------------------

template< typename ErrorType, int DefaultErrorValue >
bool Error< ErrorType, DefaultErrorValue >::isErrorSet() const
{
	return (((ErrorType)DefaultErrorValue) == m_eErrorCode ? false : true);
}

// ---------------------------------------------------------------

template< typename ErrorType, int DefaultErrorValue >
Error< ErrorType, DefaultErrorValue > & Error< ErrorType, DefaultErrorValue >::operator=(
	Error< ErrorType, DefaultErrorValue > const & kOther
	)
{
	return setError( kOther.m_eErrorCode );
}

// ---------------------------------------------------------------

template< typename ErrorType, int DefaultErrorValue >
Error< ErrorType, DefaultErrorValue > & Error< ErrorType, DefaultErrorValue >::operator=(
	ErrorType const & eErrorCode
	)
{
	return setError( eErrorCode );
}

// ---------------------------------------------------------------

template< typename ErrorType, int DefaultErrorValue >
bool Error< ErrorType, DefaultErrorValue >::operator==(
	Error< ErrorType, DefaultErrorValue > const & kOther
	) const
{
	return m_eErrorCode == kOther.m_eErrorCode;
}

// ---------------------------------------------------------------

template< typename ErrorType, int DefaultErrorValue >
bool Error< ErrorType, DefaultErrorValue >::operator==(
	ErrorType const & eErrorCode
	) const
{
	return m_eErrorCode == eErrorCode;
}

// ---------------------------------------------------------------

}; // namespace Error
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* ERROR_HXX_ */
