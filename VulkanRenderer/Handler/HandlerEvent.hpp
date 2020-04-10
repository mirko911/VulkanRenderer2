#pragma once

#include <unordered_map>
#include <functional>
#include <vector>
#include <string>

#include <loguru.hpp>

struct Event {};

struct EventKeyPress : public Event {
	const int key;
	const int scancode;
	const int action;
	const int mods;

	 EventKeyPress(const int _key, const int _scancode, const int _action, const int _mods)
		: key(_key), scancode(_scancode), action(_action), mods(_mods)
	{};
};

struct EventMouseMove : public Event {
	const double x;
	const double y;
	EventMouseMove(const double _x, const double _y) :
		x(_x), y(_y)
	{};
};

typedef std::function<void(Event&)> callbackFunction;


class HandlerEvent {
private:
	std::unordered_map<std::string, std::vector<callbackFunction>> m_events;
	int32_t eventID = 0;
public:
	static HandlerEvent& instance();

	int32_t registerEvent(const std::string& eventName, callbackFunction cb);
	void unregisterEvent(const std::string& eventName, const int32_t ID);

	void notify(const std::string& eventName, Event& event);
};