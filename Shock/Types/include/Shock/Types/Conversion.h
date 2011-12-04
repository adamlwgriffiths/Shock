/*
 * Conversion.h
 *
 *  Created on: 03/07/2010
 *      Author: Adam Griffiths
 */

#ifndef CONVERSION_H_
#define CONVERSION_H_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Error/Error.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Consts {
namespace Types {

// ---------------------------------------------------------------

namespace ConversionError
{
	enum _t
	{
		Success,
		Overflow,
	};
};

// ---------------------------------------------------------------

}; // namespace Types
}; // namespace Consts
}; // namespace Shock

// ---------------------------------------------------------------

namespace Shock {
namespace Types {

// ---------------------------------------------------------------

typedef Shock::Error::Error<
	Shock::Consts::Types::ConversionError::_t,
	Shock::Consts::Types::ConversionError::Success
	>	ConversionError;
/*
class ConversionError
{
	public:
		enum _t
		{
			Success,
			Overflow,
		};

		ConversionError() :
				m_eError( Success )
			{
			};

		explicit ConversionError( _t const & eError ) :
					m_eError( eError )
			{
			};
		~ConversionError()
			{
			};

		void				clear()
			{
				m_eError = Success;
			};

		ConversionError &	setError( _t const & eError )
			{
				m_eError = eError;
				return *this;
			};

		_t			getError() const
			{
				return m_eError;
			};

		bool		isErrorSet() const
			{
				return (Success == m_eError ? false : true);
			};

		ConversionError &	operator=( ConversionError const & kOther )
			{
				m_eError = kOther.m_eError;
				return *this;
			};

	private:
		_t				m_eError;
};
*/
// ---------------------------------------------------------------

template < typename InType, typename OutType >
class Conversion
{
	private:
		Conversion() {};
		~Conversion() {};

	public:
		static OutType			convert( InType iIn, ConversionError & kError );
};

// ---------------------------------------------------------------

}; // namespace Types
}; // namespace Shock

// ---------------------------------------------------------------

// include our template implementation
#include "Shock/Types/Conversion.hxx"

// ---------------------------------------------------------------

#endif /* CONVERSION_H_ */
