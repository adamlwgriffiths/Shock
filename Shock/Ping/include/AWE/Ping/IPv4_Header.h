#pragma once

// ---------------------------------------------------------------
// Core Includes
#include "AWE/Core/Core.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Network {

// ---------------------------------------------------------------

struct IPv4_Header
{
	AWE::uint32		h_len:4;		// Length of the header in dwords
	AWE::uint32		version:4;		// Version of IP
	AWE::uint8		tos;			// Type of service
	AWE::uint16		total_len;		// Length of the packet in dwords
	AWE::uint16		ident;			// unique identifier
	AWE::uint16		flags;			// Flags
	AWE::uint8		ttl;			// Time to live
	AWE::uint8		proto;			// Protocol number (TCP, UDP etc)
	AWE::uint16		checksum;		// IP checksum

	AWE::uint32		source_ip;
	AWE::uint32		dest_ip;
};

// ---------------------------------------------------------------

}; // namespace Network
}; // namespace AWE

// ---------------------------------------------------------------
