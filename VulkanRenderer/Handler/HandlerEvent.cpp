#include "HandlerEvent.hpp"
#include "../GameRoot.hpp"

HandlerEvent& HandlerEvent::instance()
{
	static HandlerEvent handler;
	return handler;
}

int32_t HandlerEvent::registerEvent(const std::string& eventName, callbackFunction cb)
{

	m_events[eventName].emplace_back(cb);

	return eventID++;
}

void HandlerEvent::unregisterEvent(const std::string& eventName, const int32_t ID)
{
	ABORT_F("Event unregisterEvent not implemented");
}

void HandlerEvent::notify(const std::string& eventName, Event& event)
{
	if (m_events.find(eventName) == m_events.end()) {
		return;
	}

	//LOG_F(INFO, "[EventHandler] Notify %s", eventName.c_str());

	for (auto eventCallback : m_events[eventName]) {
		eventCallback(event);
	}
}

//void HandlerEvent::notify(const std::string& eventName, Event* event)
//{
//	if (m_events.find(eventName) == m_events.end()) {
//		return;
//	}
//
//	//LOG_F(INFO, "[EventHandler] Notify %s", eventName.c_str());
//
//	for (auto eventCallback : m_events[eventName]) {
//		eventCallback(event);
//	}
//}

EventDrawCall::EventDrawCall(GameRoot& _gameRoot) : gameRoot(_gameRoot)
{
}
