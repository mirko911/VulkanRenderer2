#pragma once

#include "InputBase.hpp"

class InputMouse : public InputBase {
private:
	Window m_window;
public:
	void Init(VulkanDevice& device) override;
	void onMouseCallback(EventMouseMove& event);
};