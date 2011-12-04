/*
 * Semaphore.h
 *
 *  Created on: 15/12/2010
 *      Author: adam
 */

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Platform/Platform.h"
#include "Shock/Types/Types.h"

// ---------------------------------------------------------------

namespace Shock {
namespace Thread {

// ---------------------------------------------------------------

class Semaphore
{
	public:
		Semaphore(
			Shock::Types::size_t iInitialCount = 1
			);
		~Semaphore();

		void				acquire();
		bool				tryAquire();
		void				release();

	private:
		HANDLE		m_kSemaphore;
};

// ---------------------------------------------------------------

}; // namespace Thread
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* SEMAPHORE_H_ */
