#pragma once

// ---------------------------------------------------------------
// Socket Includes
#include "AWE/Socket/Protocol.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

class DatagramProtocol :
	public AWE::Socket::Protocol
{
	public:
		DatagramProtocol( Socket* pSocket );
		virtual ~DatagramProtocol();

		virtual int				getSocketType() const;

		void					setRawSocket( bool bRawSocket );

		virtual AWE::int32		sendTo(
			Address const& kAddress,
			AWE::int8 const* pData,
			AWE::uint32 iLength
			);
		virtual AWE::int32		receiveFrom(
			Address* pAddress,
			AWE::int8* pData,
			AWE::uint32 iMaxLength
			);

		virtual AWE::int32		send(
			AWE::int8 const* pData,
			AWE::uint32 iLength
			);
		virtual AWE::int32		receive(
			AWE::int8* pData,
			AWE::uint32 iMaxLength
			);

	protected:
		int						m_iSocketType;
};

// ---------------------------------------------------------------

template < int ProtocolType >
class DatagramProtocolTemplate :
	public AWE::Socket::DatagramProtocol
{
	public:
		DatagramProtocolTemplate( Socket* pSocket ) :
				DatagramProtocol( pSocket )
			{};

		virtual ~DatagramProtocolTemplate()
			{};

		virtual int				getProtocol() const
			{
				return ProtocolType;
			};
};

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------
