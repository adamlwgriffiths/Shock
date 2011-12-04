/*
 * TimeAccumulator.cpp
 *
 *  Created on: 14/12/2010
 *      Author: adam
 */

#include "Shock/Time/TimeAccumulator.h"

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/SafeInteger/Operations.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Time {

// ---------------------------------------------------------------

TimeAccumulator::TimeAccumulator() :
	m_iAccumulatedTime( 0 )
{
}

// ---------------------------------------------------------------

TimeAccumulator::~TimeAccumulator()
{
}

// ---------------------------------------------------------------

void TimeAccumulator::addTime(
	Shock::Types::uint64_t const & iDelta,
	Shock::Types::ConversionError & kError
	)
{
	m_iAccumulatedTime = Shock::SafeInteger::Operations< Shock::Types::uint64_t >::add(
		m_iAccumulatedTime,
		iDelta,
		kError
		);
}

// ---------------------------------------------------------------

void TimeAccumulator::addTime(
	Shock::Time::Time const & kTime,
	Shock::Types::ConversionError & kError
	)
{
	m_iAccumulatedTime = Shock::SafeInteger::Operations< Shock::Time::Time::time_t >::add(
		m_iAccumulatedTime,
		kTime.getTime(
			Shock::Consts::Time::MilliSeconds,
			kError
			),
		kError
		);
}

// ---------------------------------------------------------------

void TimeAccumulator::addTime(
	Shock::Time::TimeDifference const & kTimeDifference,
	Shock::Types::ConversionError & kError
	)
{
	m_iAccumulatedTime = Shock::SafeInteger::Operations< Shock::Time::TimeDifference::time_t >::add(
		m_iAccumulatedTime,
		kTimeDifference.getTime(
			Shock::Consts::Time::MilliSeconds,
			kError
			),
		kError
		);
}

// ---------------------------------------------------------------

void TimeAccumulator::decrementTime(
	Shock::Types::uint64_t const & iDelta,
	Shock::Types::ConversionError & kError
	)
{
	m_iAccumulatedTime = Shock::SafeInteger::Operations< Shock::Types::uint64_t >::subtract(
		m_iAccumulatedTime,
		iDelta,
		kError
		);
}

// ---------------------------------------------------------------

Shock::Types::uint64_t const & TimeAccumulator::getAccumulatedTime() const
{
	return m_iAccumulatedTime;
}

// ---------------------------------------------------------------

}; // namespace Time
}; // namespace Shock

// ---------------------------------------------------------------

