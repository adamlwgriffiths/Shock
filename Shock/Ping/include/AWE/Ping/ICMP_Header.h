#pragma once

// ---------------------------------------------------------------
// Core Includes
#include "AWE/Core/Core.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Network {

// ---------------------------------------------------------------

struct ICMP_Header
{
	AWE::uint8		type;			// ICMP packet type
	AWE::uint8		code;			// Type sub code
	AWE::uint16		checksum;		// checksum of packet
	AWE::uint16		id;
	AWE::uint16		seq;
};

// ---------------------------------------------------------------

}; // namespace Network
}; // namespace AWE

// ---------------------------------------------------------------
