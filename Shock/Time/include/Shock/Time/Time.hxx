/*
 * Time.hxx
 *
 *  Created on: 08/11/2010
 *      Author: adam
 */

#ifndef TIME_HXX_
#define TIME_HXX_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/SafeInteger/Operations.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Time {

// ---------------------------------------------------------------
// Static / Global Variables
template < typename T >
typename TimeTemplate< T >::time_t const		TimeTemplate< T >::s_iMagnitude3	= 1000;

// ---------------------------------------------------------------

template < typename T >
TimeTemplate< T >::TimeTemplate(
	Shock::Time::TimeTemplate< T >::time_t const & iTime,
	Shock::Time::Base const & kBase
	) :
	m_kBase( kBase ),
	m_iTime( iTime )
{
}

// ---------------------------------------------------------------

template < typename T >
TimeTemplate< T >::TimeTemplate(
	TimeTemplate< T > const & kOther
	) :
	m_kBase( kOther.m_kBase ),
	m_iTime( kOther.m_iTime )
{
}

// ---------------------------------------------------------------

template < typename T >
TimeTemplate< T >::~TimeTemplate()
{
}

// ---------------------------------------------------------------

template < typename T >
Shock::Time::Base const & TimeTemplate< T >::getBase() const
{
	return m_kBase;
}

// ---------------------------------------------------------------

template < typename T >
typename Shock::Time::TimeTemplate< T >::time_t TimeTemplate< T >::getTime(
	Shock::Time::Base const & kBase,
	Shock::Types::ConversionError & kError
	) const
{
	return convertBase(
		m_iTime,
		m_kBase,
		kBase,
		kError
		);
}

// ---------------------------------------------------------------

template < typename T >
void TimeTemplate< T >::setTime(
	typename Shock::Time::TimeTemplate< T >::time_t const & iTime,
	Shock::Time::Base const & kBase
	)
{
	m_kBase.setBase( kBase.getBase() );
	m_iTime = iTime;
}

// ---------------------------------------------------------------

template < typename T >
bool TimeTemplate< T >::operator==(
	Shock::Time::TimeTemplate< T > const & kOther
	) const
{
	Shock::Types::ConversionError kError;

	// get the lowest base
	Shock::Time::Base kLowestBase(
		(int)(m_kBase.getBase()) < (int)(kOther.getBase().getBase()) ?
			m_kBase :
			kOther.getBase()
		);

	// convert to the lowest base and compare
	bool bEqual(
		getTime( kLowestBase, kError ) ==
		kOther.getTime( kLowestBase, kError )
		);

	// check for errors
	// this ensures we catch the edge case of
	// a zero time of a low base vs a non-zero time
	// of a high base that overflows and becomes zero
	if ( true == kError.isErrorSet() )
	{
		bEqual = false;
	}

	return bEqual;
}

// ---------------------------------------------------------------

template < typename T >
typename Shock::Time::TimeTemplate< T >::time_t TimeTemplate< T >::convertBase(
	typename Shock::Time::TimeTemplate< T >::time_t const & iTime,
	Shock::Time::Base const & kInputBase,
	Shock::Time::Base const & kOutputBase,
	Shock::Types::ConversionError & kError
	) const
{
	time_t iResult( iTime );

	int iBaseDifference(
		kOutputBase.getBase() - kInputBase.getBase()
		);

	if ( 0 > iBaseDifference )
	{
		// we are moving to smaller units (eg seconds > micro)
		// multiply our value

		// calculate our magnitude change
		// change = 1 magnitude value * num magnitudes changed
		time_t iMagnitude(
			(-iBaseDifference) * s_iMagnitude3
			);

		// divide our time
		Shock::SafeInteger::Operations< time_t >::multiply(
			iTime,
			iMagnitude,
			kError
			);
	}
	else if ( 0 < iBaseDifference )
	{
		// we are moving to bigger units (eg mico > seconds)
		// divide our value

		// calculate our magnitude change
		// change = 1 magnitude value * num magnitudes changed
		time_t iMagnitude(
			iBaseDifference * s_iMagnitude3
			);

		// divide our time
		Shock::SafeInteger::Operations< time_t >::divide(
			iTime,
			iMagnitude,
			kError
			);
	}
	else
	{
		// no change in magnitude
	}

	return iResult;
}

// ---------------------------------------------------------------

}; // namespace Time
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* TIME_HXX_ */
