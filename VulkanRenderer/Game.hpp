#pragma once
#include <loguru.hpp>

#include "VulkanDevice.hpp"
#include "Window.hpp"

#include "Renderer.hpp"
#include "GameRoot.hpp"
#include "GeoCube.hpp"

class Game
{
private:
	VulkanDevice m_device;
	Window m_window;
	Renderer m_renderer;
	GameRoot m_gameRoot;
public:
	void Init(VulkanDevice& device, Window& window);
	void Tick();
	void Draw();
	void Fini();
};

