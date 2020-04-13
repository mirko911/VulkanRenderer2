#pragma once

#include "InputBase.hpp"

class InputMouse : public InputBase {
private:
	Window m_window;
	double m_xPrev = 0;
	double m_yPrev = 0;
	EventMouseMove m_eventMouseMove;
public:
	void Init(VulkanDevice& device) override;
	void onMouseCallback(EventMouseMove& event);
	void update(const float ftimeDelta, GameRoot& gameRoot) override;
	void setCursorCenter();
};