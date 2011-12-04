/*
 * SafeInteger.h
 *
 *  Created on: 01/11/2010
 *      Author: adam
 */

#ifndef SAFEINTEGER_H_
#define SAFEINTEGER_H_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Types/Limits.h"
#include "Shock/Types/Types.h"
#include "Shock/Types/Conversion.h"

// ---------------------------------------------------------------

namespace Shock {
namespace SafeInteger {

// ---------------------------------------------------------------

// TODO: add a SafeIntegerThrow type that doesn't receive
// an error object, but instead provides its own
// and throws an exception when an error code is set
// TODO: convert the error code to Shock/Types/Conversion.h Errors enum

template < typename T >
class SafeInteger
{
	public:
		explicit SafeInteger( T const & iValue ) :
				m_iValue( iValue )
			{
			};
		~SafeInteger()
			{
			};

		T					getValue() const
			{
				return m_iValue;
			};

		T					getMaximum() const
			{
				return Shock::Types::Limits< T >::maximum();
			};

		T					getMinimum() const
			{
				return Shock::Types::Limits< T >::minimum();
			};

		SafeInteger< T >&		add(
				T const & iValue,
				Shock::Types::ConversionError & kError
				)
			{
				m_iValue = Shock::SafeInteger::Operations< T >::add(
					m_iValue,
					iValue,
					kError
					);

				return *this;
			};

		SafeInteger< T >&		add(
				SafeInteger< T > const & kValue,
				Shock::Types::ConversionError & kError
				)
			{
				return add( kValue.getValue(), kError );
			};

		SafeInteger< T >&		subtract(
				T const & iValue,
				Shock::Types::ConversionError & kError
				)
			{
				m_iValue = Shock::SafeInteger::Operations< T >::subtract(
					m_iValue,
					iValue,
					kError
					);

				return *this;
			};

		SafeInteger< T >&		subtract(
				SafeInteger< T > const & kValue,
				Shock::Types::ConversionError & kError
				)
			{
				return subtract( kValue.getValue(), kError );
			};

		SafeInteger< T >&		multiply(
				T const & iValue,
				Shock::Types::ConversionError & kError
				)
			{
				m_iValue = Shock::SafeInteger::Operations< T >::multiply(
					m_iValue,
					iValue,
					kError
					);

				return *this;
			};

		SafeInteger< T >&		multiply(
				SafeInteger< T > const & kValue,
				Shock::Types::ConversionError & kError
				)
			{
				return multiply( kValue.getValue(), kError );
			};

		SafeInteger< T >&		divide(
				T const & iDivisor,
				Shock::Types::ConversionError & kError
				)
			{
				m_iValue = Shock::SafeInteger::Operations< T >::divide(
					m_iValue,
					iDivisor,
					kError
					);

				return *this;
			};

		SafeInteger< T >&		divide(
				SafeInteger< T > const & kValue,
				Shock::Types::ConversionError & kError
				)
			{
				return divide( kValue.getValue(), kError );
			};

		SafeInteger< T >&		modulo(
				size_t const & iDivisor,
				Shock::Types::ConversionError & kError
				)
			{
				m_iValue = Shock::SafeInteger::Operations< T >::modulo(
					m_iValue,
					iDivisor,
					kError
					);

				return *this;
			};

		SafeInteger< T >&		modulo(
				SafeInteger< T > const & kValue,
				Shock::Types::ConversionError & kError
				)
			{
				return modulo( kValue.getValue(), kError );
			};

		SafeInteger< T >&		negative( Shock::Types::ConversionError & kError )
			{
				m_iValue = Shock::SafeInteger::Operations< T >::negative(
					m_iValue,
					kError
					);

				return *this;
			};

		SafeInteger< T >&		negative(
				SafeInteger< T > const & kValue,
				Shock::Types::ConversionError & kError
				)
			{
				return negative( kValue.getValue(), kError );
			};

		SafeInteger< T >&		leftShift(
				size_t const & iNumBits,
				Shock::Types::ConversionError & kError
				)
			{
				m_iValue = Shock::SafeInteger::Operations< T >::leftShift(
					m_iValue,
					iNumBits,
					kError
					);

				return *this;
			};

		SafeInteger< T >&		leftShift(
				SafeInteger< T > const & kValue,
				Shock::Types::ConversionError & kError
				)
			{
				return leftShift( kValue.getValue(), kError );
			};

		SafeInteger< T >&		increment( Shock::Types::ConversionError & kError )
			{
				m_iValue = Shock::SafeInteger::Operations< T >::increment(
					m_iValue,
					kError
					);
				return *this;
			};

		SafeInteger< T >&		decrement( Shock::Types::ConversionError & kError )
			{
				m_iValue = Shock::SafeInteger::Operations< T >::decrement(
					m_iValue,
					kError
					);
				return *this;
			};

		SafeInteger< T >&		operator=( T const & iValue )
			{
				m_iValue = iValue;
				return *this;
			};

		bool				operator==( T const & iValue )
			{
				return m_iValue == iValue;
			};
		bool				operator!=( T const & iValue )
			{
				return m_iValue != iValue;
			};

		bool				operator<( T const & iValue )
			{
				return m_iValue < iValue;
			};
		bool				operator<=( T const & iValue )
			{
				return m_iValue <= iValue;
			};
		bool				operator>( T const & iValue )
			{
				return m_iValue > iValue;
			};
		bool				operator>=( T const & iValue )
			{
				return m_iValue >= iValue;
			};

	private:
		T			m_iValue;
};

// ---------------------------------------------------------------

}; // namespace SafeInteger
}; // namespace Shock

// ---------------------------------------------------------------

// include our template implementation
#include "Shock/SafeInteger/SafeInteger.hxx"

// ---------------------------------------------------------------

#endif /* SAFEINTEGER_H_ */
