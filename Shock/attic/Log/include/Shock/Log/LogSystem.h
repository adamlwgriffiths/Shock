/*
 * LogSystem.h
 *
 *  Created on: 24/10/2010
 *      Author: adam
 */

#ifndef LOGSYSTEM_H_
#define LOGSYSTEM_H_

// ---------------------------------------------------------------
// Standard Includes
#include <string>

// ---------------------------------------------------------------

namespace Shock {
namespace Consts {
namespace Logging {

// ---------------------------------------------------------------

namespace LogLevel
{
	enum _t
	{
		Debug,								// Debugging information
		Information,					// Application information
		Warning,							// Possibly undesired, execution continuing
		Error,								// An error occured, possibly recoverable
		Fatal									// A fatal error occured, no recovery
	};
};

// ---------------------------------------------------------------

}; // namespace Logging
}; // namespace Consts
}; // namespace Shock

// ---------------------------------------------------------------

namespace Shock {
namespace Logging {

// ---------------------------------------------------------------

/*!
 * \note This class is thread safe.
 */
class LogSystem
{
	// TODO: un-stub this class
	// TODO: implement a singleton template in a "Patterns" library
	private:
		LogSystem()
		{};
		~LogSystem()
		{};

	public:
		LogSystem&				instance()
			{
				static LogSystem sLogSystem;
				return sLogSystem;
			};

		void					log(
			Shock::Consts::Logging::LogLevel eLevel,
			std::string const & sMessage
			)
			{};
};


// ---------------------------------------------------------------

}; // namespace Logging
}; // namespace Shock

// ---------------------------------------------------------------


#endif /* LOGSYSTEM_H_ */
