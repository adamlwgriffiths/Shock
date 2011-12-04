/*
 * Limits.hxx
 *
 *  Created on: 07/11/2010
 *      Author: adam
 */

#ifndef LIMITS_HXX_
#define LIMITS_HXX_

// ---------------------------------------------------------------

namespace Shock {
namespace Types {

// ---------------------------------------------------------------

template <>
inline
Shock::Types::uint8_t Limits< Shock::Types::uint8_t >::getMaximum()
{
	return Shock::Consts::Types::Uint8::Max;
};

// ---------------------------------------------------------------

template <>
inline
Shock::Types::uint8_t Limits< Shock::Types::uint8_t >::getMinimum()
{
	return Shock::Consts::Types::Uint8::Min;
};

// ---------------------------------------------------------------

template <>
inline
Shock::Types::uint16_t Limits< Shock::Types::uint16_t >::getMaximum()
{
	return Shock::Consts::Types::Uint16::Max;
};

// ---------------------------------------------------------------

template <>
inline
Shock::Types::uint16_t Limits< Shock::Types::uint16_t >::getMinimum()
{
	return Shock::Consts::Types::Uint16::Min;
};

// ---------------------------------------------------------------

template <>
inline
Shock::Types::uint32_t Limits< Shock::Types::uint32_t >::getMaximum()
{
	return Shock::Consts::Types::Uint32::Max;
};

// ---------------------------------------------------------------

template <>
inline
Shock::Types::uint32_t Limits< Shock::Types::uint32_t >::getMinimum()
{
	return Shock::Consts::Types::Uint32::Min;
};

// ---------------------------------------------------------------

template <>
inline
Shock::Types::uint64_t Limits< Shock::Types::uint64_t >::getMaximum()
{
	return Shock::Consts::Types::Uint64::Max;
};

// ---------------------------------------------------------------

template <>
inline
Shock::Types::uint64_t Limits< Shock::Types::uint64_t >::getMinimum()
{
	return Shock::Consts::Types::Uint64::Min;
};

// ---------------------------------------------------------------

template <>
inline
Shock::Types::int8_t Limits< Shock::Types::int8_t >::getMaximum()
{
	return Shock::Consts::Types::Int8::Max;
};

// ---------------------------------------------------------------

template <>
inline
Shock::Types::int8_t Limits< Shock::Types::int8_t >::getMinimum()
{
	return Shock::Consts::Types::Int8::Min;
};

// ---------------------------------------------------------------

template <>
inline
Shock::Types::int16_t Limits< Shock::Types::int16_t >::getMaximum()
{
	return Shock::Consts::Types::Int16::Max;
};

// ---------------------------------------------------------------

template <>
inline
Shock::Types::int16_t Limits< Shock::Types::int16_t >::getMinimum()
{
	return Shock::Consts::Types::Int16::Min;
};

// ---------------------------------------------------------------

template <>
inline
Shock::Types::int32_t Limits< Shock::Types::int32_t >::getMaximum()
{
	return Shock::Consts::Types::Int32::Max;
};

// ---------------------------------------------------------------

template <>
inline
Shock::Types::int32_t Limits< Shock::Types::int32_t >::getMinimum()
{
	return Shock::Consts::Types::Int32::Min;
};

// ---------------------------------------------------------------

template <>
inline
Shock::Types::int64_t Limits< Shock::Types::int64_t >::getMaximum()
{
	return Shock::Consts::Types::Int64::Max;
};

// ---------------------------------------------------------------

template <>
inline
Shock::Types::int64_t Limits< Shock::Types::int64_t >::getMinimum()
{
	return Shock::Consts::Types::Int64::Min;
};

// ---------------------------------------------------------------

}; // namespace Types
}; // namespace Shock

// ---------------------------------------------------------------

#endif /* LIMITS_HXX_ */
