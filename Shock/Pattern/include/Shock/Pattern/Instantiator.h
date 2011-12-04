/*
 * Instantiator.h
 *
 *  Created on: 22/12/2010
 *      Author: adam
 */

#ifndef INSTANTIATOR_H_
#define INSTANTIATOR_H_

// ---------------------------------------------------------------
// Standard Includes
#include <string>

// ---------------------------------------------------------------

namespace Shock {
namespace Pattern {

// ---------------------------------------------------------------

template < typename T >
class Instantiator
{
	public:
		virtual ~Instantiator();
		virtual T*			create() const = 0;
		void				destroy( T* pObject ) const;

		std::string const &	getObjectType() const;

	protected:
		explicit Instantiator( char const * sObjectType );
		Instantiator( std::string const & sObjectType );

	private:
		std::string					m_sObjectType;
};

// ---------------------------------------------------------------

}; // namespace Pattern
}; // namespace Shock

// ---------------------------------------------------------------

// include our template implementation
#include "Shock/Pattern/Instantiator.hxx"

// ---------------------------------------------------------------

#endif /* INSTANTIATOR_H_ */
