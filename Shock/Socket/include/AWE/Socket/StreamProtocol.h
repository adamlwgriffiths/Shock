#pragma once

// ---------------------------------------------------------------
// Core Includes
#include "AWE/Core/HashSet.h"

// Socket Includes
#include "AWE/Socket/Protocol.h"

// ---------------------------------------------------------------

namespace AWE {
namespace Socket {

// ---------------------------------------------------------------

class StreamProtocol :
	public AWE::Socket::Protocol
{
	// ---------------------------------------------------------------
	// Friends
	template < class T >
	friend class StreamProtocolHost;

	public:
		// ---------------------------------------------------------------
		// Typedefs

		AWE_TYPEDEF_POINTER_HASH_SET( StreamProtocol, AWE::Socket::StreamProtocol* )		StreamSocketContainer;
/*
		AWE_POINTER_HASH_FUNCTION_DEFINITION(
			StreamProtocol,
			AWE::Socket::StreamProtocol*
			);

		typedef AWE_STD_EXT::hash_set<
			AWE::Socket::StreamProtocol*,
			AWE_POINTER_HASH_FUNCTION_NAME( StreamProtocol )
			>		StreamSocketContainer;
*/
		// ---------------------------------------------------------------

		StreamProtocol( Socket* pSocket );
		virtual ~StreamProtocol();

		virtual int				getSocketType() const;

		StreamProtocol*			getParent();
		StreamSocketContainer::const_iterator	getChildrenBegin() const;
		StreamSocketContainer::const_iterator	getChildrenEnd() const;

		virtual AWE::int32		send(
			AWE::int8 const* pData,
			AWE::uint32 iLength
			);
		virtual AWE::int32		receive(
			AWE::int8* pData,
			AWE::uint32 iMaxLength
			);

	protected:
		StreamProtocol( Socket* pSocket, StreamProtocol* pParent );

		void					addChild( StreamProtocol* pChild );
		void					removeChild( StreamProtocol* pChild );
		void					removeParent();

		int						m_iSocketType;

		AWE::Socket::StreamProtocol*	m_pParent;
		StreamSocketContainer	m_kChildren;
};

// ---------------------------------------------------------------

template < int ProtocolType >
class StreamProtocolTemplate :
	public AWE::Socket::StreamProtocol
{
	// ---------------------------------------------------------------
	// Friends
	template < class T >
	friend class StreamProtocolHost;

	public:
		StreamProtocolTemplate( Socket* pSocket );
		virtual ~StreamProtocolTemplate();

		virtual int				getProtocol() const;

	protected:
		StreamProtocolTemplate( Socket* pSocket, StreamProtocolTemplate* pParent );
};

// ---------------------------------------------------------------

}; // namespace Socket
}; // namespace AWE

// ---------------------------------------------------------------

#ifndef AWE_TEMPLATE_EXPORT_KEYWORD
#	include "StreamProtocol.hxx"
#endif

// ---------------------------------------------------------------
