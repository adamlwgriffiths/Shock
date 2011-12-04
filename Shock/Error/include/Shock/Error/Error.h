/*
 * Error.h
 *
 *  Created on: 04/01/2011
 *      Author: adam
 */

#ifndef ERROR_H_
#define ERROR_H_

// ---------------------------------------------------------------

namespace Shock {
namespace Error {

// ---------------------------------------------------------------

/*!
 * Inherit from this to create error classes.
 * Put error enumerations in the Shock::Const namespace
 * and pass in as template parameter T
 */
template < typename ErrorType, int DefaultErrorValue = 0 >
class Error
{
	public:
		Error();
		explicit Error( ErrorType const & eErrorCode );
		virtual ~Error();

		void				clear();
		Error< ErrorType, DefaultErrorValue > &	setError( ErrorType const & eErrorCode );
		ErrorType const &	getError() const;
		bool				isErrorSet() const;

		Error< ErrorType, DefaultErrorValue > &	operator=(
			Error< ErrorType, DefaultErrorValue > const & kOther
			);
		Error< ErrorType, DefaultErrorValue > &	operator=(
			ErrorType const & eErrorCode
			);
		bool				operator==(
			Error< ErrorType, DefaultErrorValue > const & kOther
			) const;
		bool				operator==(
			ErrorType const & eErrorCode
			) const;

	protected:
		ErrorType			m_eErrorCode;
};

// ---------------------------------------------------------------

/*!
 * \brief Global operator to allow Enum == ErrorObject comparisson
 */
template < typename ErrorType, int DefaultErrorValue >
bool operator==( ErrorType const & eErrorCode, Error< ErrorType, DefaultErrorValue > const & kOther )
{
	return kOther == eErrorCode;
};

// ---------------------------------------------------------------

}; // namespace Error
}; // namespace Shock

// ---------------------------------------------------------------

// include our template implementation
#include "Shock/Error/Error.hxx"

// ---------------------------------------------------------------

#endif /* ERROR_H_ */
