/*
 * ThreadCommon.h
 *
 *  Created on: 05/01/2011
 *      Author: adam
 */

#ifndef THREADCOMMON_H_
#define THREADCOMMON_H_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Error/Error.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Consts {
namespace Thread {

// ---------------------------------------------------------------

namespace Error
{
	enum _t
	{
		Success,							// Success
		Error,								// Calling error
		ResumeFailed,						// Resume failed, try again
		ThreadNotSuspended,					// Thread was not previously suspended
		Timeout,							// The operation timed out
	};
};

// ---------------------------------------------------------------

}; // namespace Thread
}; // namespace Consts
}; // namespace Shock

// ---------------------------------------------------------------

namespace Shock {
namespace Thread {

// ---------------------------------------------------------------

typedef Shock::Error::Error<
	Shock::Consts::Thread::Error::_t,
	Shock::Consts::Thread::Error::Success
	>	Error;

// ---------------------------------------------------------------

}; // namespace Thread
}; // namespace Shock

// ---------------------------------------------------------------


#endif /* THREADCOMMON_H_ */
