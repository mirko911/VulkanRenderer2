#pragma once

#include <unordered_map>
#include <functional>
#include <vector>
#include <string>
#include <loguru.hpp>

struct Event {};

class GameRoot;

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
	double x;
	double y;
	double speed_x;
	double speed_y;
	EventMouseMove(const double _x, const double _y, const double _speed_x, const double _speed_y) :
		x(_x), y(_y), speed_x(_speed_x), speed_y(_speed_y)
	{};
	EventMouseMove() {};
};

struct EventAction : public Event {
	uint32_t action = 0x0;
	EventAction(const uint32_t _action) :
		action(_action)
	{};
	EventAction() {};
};

struct EventDrawCall : public Event {
	GameRoot& gameRoot;
	EventDrawCall(GameRoot& _gameRoot);
};

typedef std::function<void(Event&)> callbackFunction;


class HandlerEvent {
private:
	std::unordered_map<std::string, std::unordered_map<int32_t , callbackFunction>> m_events;
	int32_t eventID = 0;
public:
	static HandlerEvent& instance();

	int32_t registerEvent(const std::string& eventName, callbackFunction cb);
	void unregisterEvent(const std::string& eventName, const int32_t ID);

	void notify(const std::string& eventName, Event& event);
};