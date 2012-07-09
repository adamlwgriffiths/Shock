#include "AWE/Socket/TCP.h"
// ---------------------------------------------------------------

namespace AWE {
namespace Socket {
namespace TCP {

// ---------------------------------------------------------------

AWE::Socket::TCP::Protocol*		create()
{
	return new AWE::Socket::TCP::Protocol( new Socket() );
}

// ---------------------------------------------------------------

}; // namespace TCP
}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
