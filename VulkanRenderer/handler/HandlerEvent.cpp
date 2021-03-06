#include "HandlerEvent.hpp"
#include "../GameRoot.hpp"

HandlerEvent& HandlerEvent::instance()
{
	static HandlerEvent handler;
	return handler;
}

int32_t HandlerEvent::registerEvent(const std::string& eventName, callbackFunction cb)
{
	m_events[eventName][eventID] = cb;;

	return eventID++;
}

void HandlerEvent::unregisterEvent(const std::string& eventName, const int32_t ID)
{
	if (ID == ENTITY_NOT_FOUND) {
		return;
	}
	m_events[eventName].erase(ID);

	LOG_F(WARNING, "Removed event %s %i", eventName.c_str(), ID);
}

void HandlerEvent::notify(const std::string& eventName, Event& event)
{
	if (m_events.find(eventName) == m_events.end()) {
		return;
	}

	for (auto eventCallback : m_events[eventName]) {
		eventCallback.second(event);
	}
}


EventDrawCall::EventDrawCall(GameRoot& _gameRoot) : gameRoot(_gameRoot)
{
}
