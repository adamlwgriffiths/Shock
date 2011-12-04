/*
 * TimeAccumulator.h
 *
 *  Created on: 14/12/2010
 *      Author: adam
 */

#ifndef TIMEACCUMULATOR_H_
#define TIMEACCUMULATOR_H_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Types/Types.h"
#include "Shock/Types/Conversion.h"
#include "Shock/Time/Time.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Time {

// ---------------------------------------------------------------

class TimeAccumulator
{
	public:
		TimeAccumulator();
		virtual ~TimeAccumulator();

		void			addTime(
			Shock::Types::uint64_t const & iDelta,
			Shock::Types::ConversionError & kError
			);
		void			addTime(
			Shock::Time::Time const & kTime,
			Shock::Types::ConversionError & kError
			);
		void			addTime(
			Shock::Time::TimeDifference const & kTimeDifference,
			Shock::Types::ConversionError & kError
			);

		void			decrementTime(
			Shock::Types::uint64_t const & iDelta,
			Shock::Types::ConversionError & kError
			);
		void			decrementTime(
			Shock::Time::Time const & kTime,
			Shock::Types::ConversionError & kError
			);
		void			decrementTime(
			Shock::Time::TimeDifference const & kTimeDifference,
			Shock::Types::ConversionError & kError
			);

		Shock::Types::uint64_t const &	getAccumulatedTime() const;

	private:
		Shock::Types::uint64_t		m_iAccumulatedTime;
};

// ---------------------------------------------------------------

}; // namespace Time
}; // namespace Shock

// ---------------------------------------------------------------


#endif /* TIMEACCUMULATOR_H_ */
