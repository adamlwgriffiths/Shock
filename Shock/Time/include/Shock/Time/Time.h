/*
 * Time.h
 *
 *  Created on: 03/07/2010
 *      Author: Adam Griffiths
 */

#ifndef TIME_H_
#define TIME_H_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Platform/Platform.h"
#include "Shock/Types/Types.h"
#include "Shock/Types/Conversion.h"
#include "Shock/Types/Limits.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Time {

// ---------------------------------------------------------------

class Base
{
	public:
		enum _t
		{
			NanoSeconds,
			MicroSeconds,
			MilliSeconds,
			Seconds,
		};

		explicit Base( _t eBase );
		Base( Base const & kOther );
		~Base();

		_t				getBase() const;
		void			setBase( _t const & eBase );
		Base&			operator=( Base const & kOther );

	private:
		_t			m_eBase;
};

// ---------------------------------------------------------------
// TODO: create a positive time class (coded below as "Time")
// TODO: create a wrapper object that accepts either a time or nothing
// sending nothing indicates infinity. This is safer than the below
// pointer method:
// 	To represent Infinity in a method receive a Time* and
//	use a null pointer to represent infinity.

// ---------------------------------------------------------------

template < typename T >
class TimeTemplate
{
	public:
		typedef T		time_t;

	protected:
		TimeTemplate(
			time_t const & iTime,
			Shock::Time::Base const & kBase
			);
		TimeTemplate(
			TimeTemplate< T > const & kOther
			);

		virtual ~TimeTemplate();

	public:
		Shock::Time::Base const &	getBase() const;

		time_t						getTime(
			Shock::Time::Base const & kBase,
			Shock::Types::ConversionError & kError
			) const;

		void						setTime(
			time_t const & iTime,
			Shock::Time::Base const & kBase
			);

		bool						operator==(
			Shock::Time::TimeTemplate< T > const & kOther
			) const;

	protected:
		time_t		convertBase(
			time_t const & iTime,
			Shock::Time::Base const & kInputBase,
			Shock::Time::Base const & kOutputBase,
			Shock::Types::ConversionError & kError
			) const;

		Shock::Time::Base		m_kBase;
		time_t					m_iTime;
		static time_t const		s_iMagnitude3;
};

// ---------------------------------------------------------------

class TimeDifference :
	public TimeTemplate< Shock::Types::int64_t >
{
	public:
		TimeDifference(
			time_t const & iTime,
			Shock::Time::Base const & kBase
			);
		TimeDifference(
			TimeDifference const & kOther
			);

		virtual ~TimeDifference();
};

// ---------------------------------------------------------------

class Time :
	public TimeTemplate< Shock::Types::uint64_t >
{
	public:
		Time(
			time_t const & iTime,
			Shock::Time::Base const & kBase
			);
		Time(
			Time const & kOther
			);

		virtual ~Time();

		TimeDifference		subtract(
			Time const & kOther,
			Shock::Types::ConversionError & kError
			);
};

// ---------------------------------------------------------------

}; // namespace Time
}; // namespace Shock

// ---------------------------------------------------------------

namespace Shock {
namespace Consts {
namespace Time {

// ---------------------------------------------------------------

Shock::Time::Base const			NanoSeconds( Shock::Time::Base::NanoSeconds );
Shock::Time::Base const			MicroSeconds( Shock::Time::Base::MicroSeconds );
Shock::Time::Base const			MilliSeconds( Shock::Time::Base::MilliSeconds );
Shock::Time::Base const			Seconds( Shock::Time::Base::Seconds );

// ---------------------------------------------------------------

}; // namespace Time
}; // namespace Consts
}; // namespace Shock

// ---------------------------------------------------------------

// include our template implementation
#include "Shock/Time/Time.hxx"

// ---------------------------------------------------------------

#endif /* TIME_H_ */
