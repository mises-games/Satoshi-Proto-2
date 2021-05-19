#include <Satoshi/stpch.hpp>
#include "MessageQueue.hpp"

#include <Satoshi/Events/KeyEvent.hpp>
#include <Satoshi/Events/MouseEvent.hpp>
#include <Satoshi/Events/ApplicationEvent.hpp>
#include <Satoshi/Events/SocketEvent.hpp>

std::mutex Satoshi::MessageQueue::s_Mutex;
bool Satoshi::MessageQueue::s_Running = true;
std::thread* Satoshi::MessageQueue::s_MessageLoop;
std::queue<Satoshi::MessageQueueData> Satoshi::MessageQueue::s_AppMessages;
EventCallbackFunction Satoshi::MessageQueue::s_Callback;

void Satoshi::MessageQueue::Start(const EventCallbackFunction& callback)
{
	s_Callback = callback;
	s_MessageLoop = new std::thread(MessageQueue::MessageLoop);
}

void Satoshi::MessageQueue::EnqueueMessage(MessageQueueData msg)
{
	s_Mutex.lock();
	s_AppMessages.push(msg);
	s_Mutex.unlock();
}

Satoshi::MessageQueueData Satoshi::MessageQueue::DequeueMessage()
{
	MessageQueueData msg;

	msg = s_AppMessages.front();
	s_Mutex.lock();
	s_AppMessages.pop();
	s_Mutex.unlock();

	return msg;
}

void Satoshi::MessageQueue::End()
{
	s_Mutex.lock();
	s_Running = false;
	while (s_AppMessages.size() > 0)
		s_AppMessages.pop();
	s_Mutex.unlock();

	s_MessageLoop->join();
	delete s_MessageLoop;
}

void Satoshi::MessageQueue::MessageLoop()
{
	MessageQueueData msg;
	while (s_Running)
	{
		if (s_AppMessages.size() != 0)
		{
			msg = DequeueMessage();
			ProcessEvents(msg);
		}
	}
}

void Satoshi::MessageQueue::ProcessEvents(Satoshi::MessageQueueData msg)
{

	switch (msg.Type)
	{
	case Satoshi::EventType::AppTicked:
	{ return; }
	case Satoshi::EventType::AppUpdated:
	{ return; }
	case Satoshi::EventType::AppRendered:
	{ return; }

	case Satoshi::EventType::SocketCreated:
	{ 
		auto data = (SocketData*)msg.Data;
		SocketCreatedEvent event(data->Host, data->Port, data->SocketType, data->IpFamily);
		delete data;
		s_Callback(event);
		return;
	}
	case Satoshi::EventType::SocketDestroyed:
	{ 
		auto data = (SocketData*)msg.Data;
		SocketDestroyedEvent event(data->Host, data->Port, data->SocketType, data->IpFamily);
		delete data;
		s_Callback(event);
		return;
	}
	case Satoshi::EventType::SocketSentMessage:
	{ 
		auto data = (SocketMessageData*)msg.Data;
		SocketSentMessageEvent event(data->Message,data->Host, data->Port, data->SocketType, data->IpFamily);
		delete data;
		s_Callback(event);
		return; 
	}
	case Satoshi::EventType::SocketReceivedMessage:
	{
		auto data = (SocketMessageData*)msg.Data;
		SocketReceivedMessageEvent event(data->Message, data->Host, data->Port, data->SocketType, data->IpFamily);
		delete data;
		s_Callback(event);
		return;
	}

	case Satoshi::EventType::KeyPressed:
	{
		auto data = (KeyPressedData*)msg.Data;
		KeyPressedEvent event(data->KeyCode, data->RepeatCount);
		delete data;
		s_Callback(event);
		return;
	}
	case Satoshi::EventType::KeyReleased:
	{
		auto data = (KeyData*)msg.Data;
		KeyReleasedEvent event(data->KeyCode);
		delete data;
		s_Callback(event);
		return;
	}
	case Satoshi::EventType::CharTyped:
	{
		auto data = (KeyData*)msg.Data;
		CharTypedEvent event(data->KeyCode);
		delete data;
		s_Callback(event);
		return;
	}

	case Satoshi::EventType::MouseButtonPressed:
	{
		auto data = (MouseButtonData*)msg.Data;
		MouseButtonPressedEvent event(data->ButtonCode);
		delete data;
		s_Callback(event);
		return;
	}
	case Satoshi::EventType::MouseButtonReleased:
	{
		auto data = (MouseButtonData*)msg.Data;
		MouseButtonReleasedEvent event(data->ButtonCode);
		delete data;
		s_Callback(event);
		return;
	}
	case Satoshi::EventType::MouseMoved:
	{
		auto data = (MousePositionData*)msg.Data;
		MouseMovedEvent event(data->XData, data->YData);
		delete data;
		s_Callback(event);
		return;
	}
	case Satoshi::EventType::MouseScrolled:
	{
		auto data = (MousePositionData*)msg.Data;
		MouseScrolledEvent event(data->XData, data->YData);
		delete data;
		s_Callback(event);
		return;
	}

	case Satoshi::EventType::WindowClosed:
	{
		WindowCloseEvent event;
		s_Callback(event);
		return;
	}
	case Satoshi::EventType::WindowResized:
	{
		auto data = (WindowResizeData*)msg.Data;
		WindowResizeEvent event(data->Width, data->Height);
		delete data;
		s_Callback(event);
		return;
	}
	case Satoshi::EventType::WindowMinimized:
	{ return; }
	case Satoshi::EventType::WindowRestored:
	{ return; }
	case Satoshi::EventType::WindowMaximized:
	{ return; }
	case Satoshi::EventType::WindowFocused:
	{ return; }
	case Satoshi::EventType::WindowLostFocus:
	{ return; }
	case Satoshi::EventType::WindowMoved:
	{ return; }

	}
}
