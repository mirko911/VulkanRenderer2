#pragma once

#include <loguru.hpp>
#include "defintions.hpp"

#include "Window.hpp"
#include "VulkanDevice.hpp"
#include "Game.hpp"

#include "Renderer.hpp"

class Engine
{
private:
	Window m_window;
	VulkanDevice m_device;
	Game m_game;
	GameState m_gameState;
	Renderer m_renderer;
public:
	void Init();
	void Loop();
	void Fini();
};

