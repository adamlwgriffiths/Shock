/*
 * Mutex
 *
 *  Created on: 15/12/2010
 *      Author: adam
 */

#ifndef MUTEX_H_
#define MUTEX_H_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Platform/Platform.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Thread {

// ---------------------------------------------------------------

class Mutex
{
	public:
		Mutex();
		~Mutex();

		void				acquire();
		bool				tryAquire();
		void				release();

	private:
		CRITICAL_SECTION		m_kCriticalSection;
};

// ---------------------------------------------------------------

}; // namespace Thread
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* MUTEX_H_ */
