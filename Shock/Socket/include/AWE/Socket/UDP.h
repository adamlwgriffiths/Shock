#pragma once

// ---------------------------------------------------------------
// Socket Includes
#include "AWE/Socket/Address.h"
#include "AWE/Socket/DatagramProtocol.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {
namespace UDP {

// ---------------------------------------------------------------
// Typedefs
typedef AWE::Socket::DatagramProtocolTemplate< IPPROTO_UDP >	Protocol;

// ---------------------------------------------------------------

AWE::Socket::UDP::Protocol*		create();

// ---------------------------------------------------------------

}; // namespace UDP
}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
