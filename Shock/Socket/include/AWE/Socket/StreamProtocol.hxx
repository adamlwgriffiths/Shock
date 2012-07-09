
// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

AWE_TEMPLATE_EXPORT template < int ProtocolType >
StreamProtocolTemplate< ProtocolType >::StreamProtocolTemplate( Socket* pSocket ) :
	StreamProtocol( pSocket )
{
};

// ---------------------------------------------------------------

AWE_TEMPLATE_EXPORT template < int ProtocolType >
StreamProtocolTemplate< ProtocolType >::StreamProtocolTemplate( Socket* pSocket, StreamProtocolTemplate* pParent ) :
	StreamProtocol( pSocket, pParent )
{
};

// ---------------------------------------------------------------

AWE_TEMPLATE_EXPORT template < int ProtocolType >
StreamProtocolTemplate< ProtocolType >::~StreamProtocolTemplate()
{
};

// ---------------------------------------------------------------

AWE_TEMPLATE_EXPORT template < int ProtocolType >
int StreamProtocolTemplate< ProtocolType >::getProtocol() const
{
	return ProtocolType;
};

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
