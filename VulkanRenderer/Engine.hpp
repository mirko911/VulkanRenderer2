#pragma once

#include <loguru.hpp>
#include "defintions.hpp"

#include "Window.hpp"
#include "VulkanDevice.hpp"
#include "Game.hpp"

class Engine
{
private:
	Window m_window;
	VulkanDevice m_device;
	Game m_game;
	GameState m_gameState;
public:
	void Init();
	void Loop();
	void Fini();
};
