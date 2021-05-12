#ifndef MESSAGE_QUEUE_HPP
#define MESSAGE_QUEUE_HPP

#include <Satoshi/stpch.hpp>
#include <Satoshi/Events/Event.hpp>
#include <Satoshi/Core/Macros.hpp>

namespace Satoshi
{
	struct MessageQueueData
	{
		EventType Type;
		void* Data;
	};

	class MessageQueue
	{
	public:
		static void Start(const EventCallbackFunction& callback);
		static void EnqueueMessage(MessageQueueData msg);
		static void End();
	private:
		static MessageQueueData DequeueMessage();
		static void MessageLoop();
		static void ProcessEvents(MessageQueueData msg);

		static EventCallbackFunction s_Callback;
		static std::mutex s_Mutex;
		static bool s_Running;
		static std::thread* s_MessageLoop;
		static std::queue<MessageQueueData> s_AppMessages;
	};
}

#endif
