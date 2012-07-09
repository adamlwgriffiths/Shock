#pragma once

// ---------------------------------------------------------------
// Socket Includes
#include "AWE/Socket/Address.h"
#include "AWE/Socket/StreamProtocol.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {
namespace TCP {

// ---------------------------------------------------------------
// Typedefs
typedef AWE::Socket::StreamProtocolTemplate< IPPROTO_TCP >	Protocol;

// ---------------------------------------------------------------

AWE::Socket::TCP::Protocol*		create();

// ---------------------------------------------------------------

}; // namespace TCP
}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
