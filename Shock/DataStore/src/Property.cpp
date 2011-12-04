/*
 * Property.cpp
 *
 *  Created on: 02/01/2011
 *      Author: adam
 */

#include "Shock/DataStore/Property.h"

// ---------------------------------------------------------------
// Shock Includes
#include "Shock/Assert/Assert.h"

// Standard Includes
#include <cstring>	// memset

// ---------------------------------------------------------------

namespace Shock {
namespace DataStore {

// ---------------------------------------------------------------
// Static / Global Varaibles
Shock::Types::size_t const		Property::s_iDefaultStringLength( 20 );
char const						Property::m_cDefaultCharacter( 0 );

// ---------------------------------------------------------------

Property::Property(
	std::string const & sName,
	Type const & eType
	) :
	m_sName( sName ),
	m_eType( eType ),
	m_kData(),
	m_sString( s_iDefaultStringLength, m_cDefaultCharacter )	// initialise our string to a default length
{
	// zero our union
	memset( &m_kData, 0, sizeof( DataUnion ) );
}

// ---------------------------------------------------------------

Property::~Property()
{
	// do nothing
}

// ---------------------------------------------------------------

std::string const & Property::getName() const
{
	return m_sName;
}

// ---------------------------------------------------------------

Property::Type const & Property::getType() const
{
	return m_eType;
}

// ---------------------------------------------------------------

Shock::Types::uint8_t Property::getUint8() const
{
	SHOCK_ASSERT( Uint8 == m_eType );
	return m_kData.mUint8;
}

// ---------------------------------------------------------------

Shock::Types::int8_t Property::getInt8() const
{
	SHOCK_ASSERT( Int8 == m_eType );
	return m_kData.mInt8;
}

// ---------------------------------------------------------------

Shock::Types::uint16_t Property::getUint16() const
{
	SHOCK_ASSERT( Uint16 == m_eType );
	return m_kData.mUint16;
}

// ---------------------------------------------------------------

Shock::Types::int16_t Property::getInt16() const
{
	SHOCK_ASSERT( Int16 == m_eType );
	return m_kData.mInt16;
}

// ---------------------------------------------------------------

Shock::Types::uint32_t Property::getUint32() const
{
	SHOCK_ASSERT( Uint32 == m_eType );
	return m_kData.mUint32;
}

// ---------------------------------------------------------------

Shock::Types::int32_t Property::getInt32() const
{
	SHOCK_ASSERT( Int32 == m_eType );
	return m_kData.mInt32;
}

// ---------------------------------------------------------------

Shock::Types::uint64_t Property::getUint64() const
{
	SHOCK_ASSERT( Uint64 == m_eType );
	return m_kData.mUint64;
}

// ---------------------------------------------------------------

Shock::Types::int64_t Property::getInt64() const
{
	SHOCK_ASSERT( Int64 == m_eType );
	return m_kData.mInt64;
}

// ---------------------------------------------------------------

Shock::Types::float32_t Property::getFloat32() const
{
	SHOCK_ASSERT( Float32 == m_eType );
	return m_kData.mFloat32;
}

// ---------------------------------------------------------------

Shock::Types::float64_t Property::getFloat64() const
{
	SHOCK_ASSERT( Float64 == m_eType );
	return m_kData.mFloat64;
}

// ---------------------------------------------------------------

bool Property::getBool() const
{
	SHOCK_ASSERT( Bool == m_eType );
	return m_kData.mBool;
}

// ---------------------------------------------------------------

std::string const & Property::getString() const
{
	SHOCK_ASSERT( String == m_eType );
	return m_sString;
}

// ---------------------------------------------------------------

void Property::setUint8( Shock::Types::uint8_t const & iUint8 )
{
	SHOCK_ASSERT( Uint8 == m_eType );
	m_kData.mUint8 = iUint8;
}

// ---------------------------------------------------------------

void Property::setInt8( Shock::Types::uint8_t const & iInt8 )
{
	SHOCK_ASSERT( Int8 == m_eType );
	m_kData.mInt8 = iInt8;
}

// ---------------------------------------------------------------

void Property::setUint16( Shock::Types::uint8_t const & iUint16 )
{
	SHOCK_ASSERT( Uint16 == m_eType );
	m_kData.mUint16 = iUint16;
}

// ---------------------------------------------------------------

void Property::setInt16( Shock::Types::uint8_t const & iInt16 )
{
	SHOCK_ASSERT( Int16 == m_eType );
	m_kData.mInt16 = iInt16;
}

// ---------------------------------------------------------------

void Property::setUint32( Shock::Types::uint8_t const & iUint32 )
{
	SHOCK_ASSERT( Uint32 == m_eType );
	m_kData.mUint32 = iUint32;
}

// ---------------------------------------------------------------

void Property::setInt32( Shock::Types::uint8_t const & iInt32 )
{
	SHOCK_ASSERT( Int32 == m_eType );
	m_kData.mInt32 = iInt32;
}

// ---------------------------------------------------------------

void Property::setUint64( Shock::Types::uint8_t const & iUint64 )
{
	SHOCK_ASSERT( Uint64 == m_eType );
	m_kData.mUint64 = iUint64;
}

// ---------------------------------------------------------------

void Property::setInt64( Shock::Types::uint8_t const & iInt64 )
{
	SHOCK_ASSERT( Int64 == m_eType );
	m_kData.mInt64 = iInt64;
}

// ---------------------------------------------------------------

void Property::setFloat32( Shock::Types::float32_t const & fFloat32 )
{
	SHOCK_ASSERT( Float32 == m_eType );
	m_kData.mFloat32 = fFloat32;
}

// ---------------------------------------------------------------

void Property::setFloat64( Shock::Types::float64_t const & fFloat64 )
{
	SHOCK_ASSERT( Float64 == m_eType );
	m_kData.mFloat64 = fFloat64;
}

// ---------------------------------------------------------------

void Property::setBool( bool const & bBool )
{
	SHOCK_ASSERT( Bool == m_eType );
	m_kData.mBool = bBool;
}

// ---------------------------------------------------------------

void Property::setString( std::string const & sString )
{
	SHOCK_ASSERT( String == m_eType );
	m_sString = sString;
}

// ---------------------------------------------------------------

}; // namespace DataStore
}; // namespace Shock

// ---------------------------------------------------------------
