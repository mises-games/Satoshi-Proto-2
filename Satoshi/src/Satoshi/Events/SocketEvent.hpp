#ifndef SOCKET_EVENT_HPP
#define SOCKET_EVENT_HPP

#include <Satoshi/stpch.hpp>
#include "Event.hpp"

namespace Satoshi
{
	struct SocketData 
	{
		std::string_view Host;
		uint16_t Port;
		int SocketType; // Serão Modificados;
		int IpFamily;  // serão modificados

		SocketData(std::string_view host, uint16_t  port, int socketMode, int ipVersion) :
			Host(host), Port(port), SocketType(socketMode), IpFamily(ipVersion)
		{
		}
	};

	struct SocketMessageData
	{
		std::string_view Message;
		std::string_view Host;
		uint16_t Port;
		int IpFamily;
		int SocketType;

		SocketMessageData(std::string_view message, std::string_view host, uint16_t  port, int socketMode, int ipVersion) :
			Message(message), Host(host), Port(port), SocketType(socketMode), IpFamily(ipVersion)
		{
		}
	};

	class SocketEvent : public Event
	{
	public:
		std::string_view GetHost() { return m_Host; }
		uint16_t GetPort() { return m_Port; }
		int GetSocketMode() { return m_SocketType; }
		int GetIpFamily() { return m_IpFamily; }
	
		EVENT_CLASS_CATEGORY(EventCategoryNetwork)
	protected:
		SocketEvent(std::string_view host, uint16_t port, int socketType, int ipFamily)
			: m_Host(host), m_Port(port), m_SocketType(socketType), m_IpFamily(ipFamily)
		{}

		std::string_view m_Host;
		uint16_t m_Port;
		int m_SocketType;
		int m_IpFamily;
	};

	class SocketCreatedEvent : public SocketEvent
	{
	public:
		SocketCreatedEvent(std::string_view host, uint16_t port, int socketType, int ipFamily) :
			SocketEvent(host, port, socketType, ipFamily) {}

		std::string ToString() const override
		{
			std::stringstream ss;

			ss << "SocketCreatedEvent: " << m_Host << ":" << m_Port << " with: "
				<< (m_SocketType == 1 ? "TCP" : "UDP") << " Server" << " and IP Version: " << (uint64_t) m_IpFamily;
			return ss.str();
		}

		EVENT_CLASS_TYPE(SocketCreated)
	};

	class SocketDestroyedEvent : public SocketEvent
	{
	public:
		SocketDestroyedEvent(std::string_view host, uint16_t port, int socketType, int ipFamily) :
			SocketEvent(host, port, socketType, ipFamily) {}

		std::string ToString() const override
		{
			std::stringstream ss;

			ss << "SocketDestroyedEvent: " << m_Host << ":" << m_Port << " with: "
				<< (m_SocketType == 1 ? "TCP" : "UDP") << " Server" << " and IP Version: " << (uint64_t)m_IpFamily;
			return ss.str();
		}

		EVENT_CLASS_TYPE(SocketDestroyed)
	};
	
	class SocketSentMessageEvent : public SocketEvent
	{
	public:
		SocketSentMessageEvent(std::string_view message, std::string_view host, uint16_t port, int socketType, int ipFamily) :
			m_Message(message), SocketEvent(host, port, socketType, ipFamily) {}

		std::string_view GetMessage() { return m_Message; }

		std::string ToString() const override
		{
			std::stringstream ss;

			ss << "SocketSentMessageEvent: " << m_Host << ":" << m_Port << " with: "
				<< (m_SocketType == 1 ? "TCP" : "UDP") << " Server" << ", IP Version: " << (uint64_t)m_IpFamily
				<< ", and following message: " << m_Message;
			return ss.str();
		}

		EVENT_CLASS_TYPE(SocketSentMessage)
	private:
		std::string_view m_Message;
	};

	class SocketReceivedMessageEvent : public SocketEvent
	{
	public:
		SocketReceivedMessageEvent(std::string_view message, std::string_view host, uint16_t port, int socketType, int ipFamily) :
			m_Message(message), SocketEvent(host, port, socketType, ipFamily) {}

		std::string_view GetMessage() { return m_Message; }

		std::string ToString() const override
		{
			std::stringstream ss;

			ss << "SocketReceivedMessageEvent: " << m_Host << ":" << m_Port << " with: "
				<< (m_SocketType == 1 ? "TCP" : "UDP") << " Server" << ", IP Version: " << (uint64_t)m_IpFamily
				<< ", and following message: " << m_Message;
			return ss.str();
		}

		EVENT_CLASS_TYPE(SocketSentMessage)
	private:
		std::string_view m_Message;
	};
}

#endif
