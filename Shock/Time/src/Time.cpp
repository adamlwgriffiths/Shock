/*
 * Time.cpp
 *
 *  Created on: 03/07/2010
 *      Author: Adam Griffiths
 */

#include "Shock/Time/Time.h"

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/SafeInteger/Operations.h"

// ---------------------------------------------------------------
// Template Instantiations
template class Shock::SafeInteger::Operations<
	Shock::Time::TimeDifference::time_t
	>;

template class Shock::SafeInteger::Operations<
	Shock::Time::Time::time_t
	>;

// ---------------------------------------------------------------

namespace Shock {
namespace Time {

// ---------------------------------------------------------------
// Static / Global variables
//template < typename T >
//typename TimeTemplate< T >::time_t const		TimeTemplate< T >::s_iMagnitude3( 1000 );

// ---------------------------------------------------------------

Base::Base( Base::_t eBase ) :
	m_eBase( eBase )
{
}

// ---------------------------------------------------------------

Base::Base( Base const & kOther ) :
	m_eBase( kOther.m_eBase )
{
}

// ---------------------------------------------------------------

Base::~Base()
{
}

// ---------------------------------------------------------------

Base::_t Base::getBase() const
{
	return m_eBase;
}

// ---------------------------------------------------------------

void Base::setBase( Base::_t const & eBase )
{
	m_eBase = eBase;
}

// ---------------------------------------------------------------

Base& Base::operator=( Base const & kOther )
{
	m_eBase = kOther.m_eBase;
	return *this;
}

// ---------------------------------------------------------------

TimeDifference::TimeDifference(
	time_t const & iTime,
	Shock::Time::Base const & kBase
	) :
	TimeTemplate< Shock::Types::int64_t >( iTime, kBase )
{
}

// ---------------------------------------------------------------

TimeDifference::TimeDifference(
	TimeDifference const & kOther
	) :
	TimeTemplate< Shock::Types::int64_t >( kOther )
{
}

// ---------------------------------------------------------------

TimeDifference::~TimeDifference()
{
}

// ---------------------------------------------------------------

Time::Time(
	time_t const & iTime,
	Shock::Time::Base const & kBase
	) :
	TimeTemplate< Shock::Types::uint64_t >( iTime, kBase )
{
}

// ---------------------------------------------------------------

Time::Time(
	Time const & kOther
	) :
	TimeTemplate< Shock::Types::uint64_t >( kOther )
{
}

// ---------------------------------------------------------------

Time::~Time()
{
}

// ---------------------------------------------------------------

TimeDifference Time::subtract(
	Time const & kOther,
	Shock::Types::ConversionError & kError
	)
{
	TimeDifference::time_t iResult( 0 );

	// get the lowest base
	Shock::Time::Base kLowestBase(
		(int)(m_kBase.getBase()) < (int)(kOther.getBase().getBase()) ?
			m_kBase :
			kOther.getBase()
		);

	{
		// convert our times
		time_t iOurTimeUnsigned(
			getTime( kLowestBase, kError )
			);
		time_t iOtherTimeUnsigned(
			kOther.getTime( kLowestBase, kError )
			);

		if ( false == kError.isErrorSet() )
		{
			// convert to signed time types
			TimeDifference::time_t iOurTime(
				Shock::Types::Conversion< time_t, TimeDifference::time_t >::convert(
					iOurTimeUnsigned,
					kError
					)
				);

			TimeDifference::time_t iOtherTime(
				Shock::Types::Conversion< time_t, TimeDifference::time_t >::convert(
					iOtherTimeUnsigned,
					kError
					)
				);

			if ( false == kError.isErrorSet() )
			{
				// calculate the time difference
				iResult = Shock::SafeInteger::Operations< Shock::Types::uint64_t >::subtract(
					iOurTime,
					iOtherTime,
					kError
					);

				// check for errors
				if ( true == kError.isErrorSet() )
				{
					iResult = 0;
				}
			}
		}
	}

	return TimeDifference(
		iResult,
		kLowestBase
		);
}

// ---------------------------------------------------------------

}; // namespace Time
}; // namespace Shock

// ---------------------------------------------------------------
