#pragma once

#include "InputBase.hpp"

class InputKeyboard : public InputBase {
private:
	Window m_window;
public:
	void Init(VulkanDevice& device) override;
	void onKeyCallback(EventKeyPress& event);
};