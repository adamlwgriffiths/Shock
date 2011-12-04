/*
 * Property.h
 *
 *  Created on: 02/01/2011
 *      Author: adam
 */

#ifndef PROPERTY_H_
#define PROPERTY_H_

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Types/Types.h"

// Standard Includes
#include <string>

// ---------------------------------------------------------------

namespace Shock {
namespace DataStore {

// ---------------------------------------------------------------

/*!
 * \brief Generic property class that requires assignment.
 *
 * Does not take a pointer to a variable which allows for
 * simple inter-thread communication without read / write
 * issues.
 */
class Property
{
	public:
		enum Type
		{
			Uint8,
			Int8,
			Uint16,
			Int16,
			Uint32,
			Int32,
			Uint64,
			Int64,
			Float32,
			Float64,
			Bool,
			String,
		};

		// Union of data
		// A class cannot live inside this, that includes the string object
		union DataUnion
		{
			Shock::Types::uint8_t		mUint8;
			Shock::Types::int8_t		mInt8;
			Shock::Types::uint8_t		mUint16;
			Shock::Types::int8_t		mInt16;
			Shock::Types::uint8_t		mUint32;
			Shock::Types::int8_t		mInt32;
			Shock::Types::uint8_t		mUint64;
			Shock::Types::int8_t		mInt64;
			Shock::Types::float32_t		mFloat32;
			Shock::Types::float64_t		mFloat64;
			bool						mBool;
		};

		explicit Property( std::string const & sName, Type const & eType );
		~Property();

		std::string const &		getName() const;
		Type const &			getType() const;

		// can't return a reference from a union
		// as the type is created on the stack when accessing the type
		Shock::Types::uint8_t	getUint8() const;
		Shock::Types::int8_t	getInt8() const;
		Shock::Types::uint16_t	getUint16() const;
		Shock::Types::int16_t	getInt16() const;
		Shock::Types::uint32_t	getUint32() const;
		Shock::Types::int32_t	getInt32() const;
		Shock::Types::uint64_t	getUint64() const;
		Shock::Types::int64_t	getInt64() const;
		Shock::Types::float32_t	getFloat32() const;
		Shock::Types::float64_t	getFloat64() const;
		bool					getBool() const;
		std::string const &		getString() const;

		void					setUint8( Shock::Types::uint8_t const & iUint8 );
		void					setInt8( Shock::Types::uint8_t const & iInt8 );
		void					setUint16( Shock::Types::uint8_t const & iUint16 );
		void					setInt16( Shock::Types::uint8_t const & iInt16 );
		void					setUint32( Shock::Types::uint8_t const & iUint32 );
		void					setInt32( Shock::Types::uint8_t const & iInt32 );
		void					setUint64( Shock::Types::uint8_t const & iUint64 );
		void					setInt64( Shock::Types::uint8_t const & iInt64 );
		void					setFloat32( Shock::Types::float32_t const & fFloat32 );
		void					setFloat64( Shock::Types::float64_t const & fFloat64 );
		void					setBool( bool const & bBool );
		void					setString( std::string const & sString );

	private:
		std::string				m_sName;
		Type					m_eType;
		DataUnion				m_kData;
		std::string				m_sString;

		static Shock::Types::size_t const	s_iDefaultStringLength;
		static char const		m_cDefaultCharacter;
};

// ---------------------------------------------------------------

}; // namespace DataStore
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* PROPERTY_H_ */
