#ifndef EVENT_HPP
#define EVENT_HPP

#include <Satoshi/stpch.hpp>

namespace Satoshi
{
	enum class EventType
	{
		None = 0,

		WindowClosed,
		WindowResized,
		WindowMinimized,
		WindowRestored,
		WindowMaximized,
		WindowFocused,
		WindowLostFocus,
		WindowMoved,

		AppTicked,
		AppUpdated,
		AppRendered,

		SocketCreated,
		SocketDestroyed,
		SocketSentMessage,
		SocketReceivedMessage,

		KeyPressed,
		KeyReleased,
		CharTyped,

		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryNetwork = BIT(1),
		EventCategoryInput = BIT(2),
		EventCategoryKeyboard = BIT(3),
		EventCategoryMouse = BIT(4),
		EventCategoryMouseButton = BIT(5),
		EventCategoryJoystick = BIT(6),

	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
		friend class EventDispatcher;
	public:
		virtual ~Event() = default;

		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	class EventDispatcher
	{
	public:
		inline EventDispatcher(Event& event) : m_Event(event) {}

		template<typename T, typename F>
		bool Dispatch(const F& function)
		{
			bool dispatched = (m_Event.GetEventType() == T::GetStaticType());
			if (dispatched)
				m_Event.Handled |= function(static_cast<T&>(m_Event));
			return dispatched;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}
#endif
