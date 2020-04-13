#pragma once

#include "InputBase.hpp"

class InputKeyboard : public InputBase {
private:
	Window m_window;
	EventAction m_eventAction;
public:
	void Init(VulkanDevice& device) override;
	void onKeyCallback(EventKeyPress& event);
	void update(const float fTimeDelta, GameRoot& gameRoot) override;
};