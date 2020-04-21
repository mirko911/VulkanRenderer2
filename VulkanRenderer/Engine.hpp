#pragma once

#include <chrono>
#include <loguru.hpp>
#include "defintions.hpp"

#include "Window.hpp"
#include "VulkanDevice.hpp"
#include "Game.hpp"


typedef std::chrono::time_point<std::chrono::high_resolution_clock> timePoint;
typedef std::chrono::high_resolution_clock HighResClock;
typedef std::chrono::nanoseconds ms;
typedef std::chrono::duration<double> fsec;

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

