#pragma once

#include <loguru.hpp>
#include "defintions.hpp"

#include "Window.hpp"
#include "VulkanDevice.hpp"

class Engine
{
private:
	Window m_window;
	VulkanDevice m_device;
public:
	void Init();
	void Loop();
	void Fini();
};

