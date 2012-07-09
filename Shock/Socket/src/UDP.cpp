#include "AWE/Socket/UDP.h"
// ---------------------------------------------------------------

namespace AWE {
namespace Socket {
namespace UDP {

// ---------------------------------------------------------------

AWE::Socket::UDP::Protocol*		create()
{
	return new AWE::Socket::UDP::Protocol( new Socket() );
}

// ---------------------------------------------------------------

}; // naemspace UDP
}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
