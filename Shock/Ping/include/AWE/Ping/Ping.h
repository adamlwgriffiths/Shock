#pragma once

// ---------------------------------------------------------------
// Core Includes
#include "AWE/Core/Core.h"
#include "AWE/Core/HighPerformanceTimer.h"
#include "AWE/Core/String.h"

// Socket Includes
#include "AWE/Socket/Address.h"
#include "AWE/Socket/Socket.h"

// Network Includes
#include "AWE/Ping/IPv4_Header.h"

// ---------------------------------------------------------------
// Pre-declarations

namespace AWE {
namespace Socket {
namespace ICMP {

class Protocol;

};
};
};

// ---------------------------------------------------------------

namespace AWE {
namespace Ping {

// ---------------------------------------------------------------

class Ping
{
	public:
		// ---------------------------------------------------------------
		// Exceptions
		AWE_DEFINE_EXCEPTION( PingException );

		// ---------------------------------------------------------------

		class Statistics
		{
			friend class Ping;

			public:
				Statistics();
				~Statistics();

				void			reset();

				AWE::uint32		getRoundTripTime() const;
				AWE::uint32		getMinimumRoundTripTime() const;
				AWE::uint32		getMaximumRoundTripTime() const;
				AWE::uint32		getAccumulatedRoundTripTime() const;
				AWE::uint32		getNumberTransmitted() const;
				AWE::uint32		getNumberReceived() const;
				bool			receivedLast() const;

			private:
				void			incrementTransmitted();
				void			incrementReceived( AWE::uint32 iRoundTripTime );

				AWE::uint32		m_iRTT;			// Round trip time
				AWE::uint32		m_iMinRTT;
				AWE::uint32		m_iMaxRTT;
				AWE::uint32		m_iAccumulatedRTT;
				AWE::uint32		m_iTransmitted;
				AWE::uint32		m_iReceived;
				bool			m_bReceivedLast;
		};



		struct PingICMP_Header
		{
			AWE::uint8		type;			// ICMP packet type
			AWE::uint8		code;			// Type sub code
			AWE::uint16		checksum;
			AWE::uint16		id;
			AWE::uint16		seq;

			AWE::uint32		timestamp;		// not part of ICMP, but we need it
		};

		Ping( AWE::Core::String const& sAddress );
		virtual ~Ping();

		int					init(
			AWE::uint32 iTimeoutMilliseconds = 1000,
			AWE::uint32 iDataLength = 32
			);
		void				shutdown();

		int					ping();

		Statistics const&		getStatistics() const;

		void				setTimeout( AWE::uint32 iTimeoutMilliSeconds );
		AWE::Core::String const&	getTargetAddress() const;

	protected:
		int					sendPing();
		int					receivePing();
		bool				parsePacket( AWE::int32 iRecvSize );

		void				setupPacket();
		void				updatePacket();
		AWE::uint16			checksum( AWE::uint16* pBuffer, AWE::uint32 iUint8_Size );

		AWE::Socket::ICMP::Protocol*	m_pICMP;

		AWE::uint32				m_iPacketSize;
		AWE::int8*				m_pICMP_Data;
		AWE::uint32				m_iDataSize;

		AWE::Core::HighPerformanceTimer*	m_pTimer;
		Statistics				m_kStats;

		AWE::Core::String		m_sAddress;
		AWE::Socket::Address	m_kAddress;

		AWE::int8*				m_pReceiveBuffer;
		AWE::uint32				m_iReceiveBufferSize;

		AWE::uint32				m_iRecvTimeout;
};

// ---------------------------------------------------------------

}; // namespace Ping
}; // namespace AWE

// ---------------------------------------------------------------
