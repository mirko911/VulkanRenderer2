#pragma once

#include <loguru.hpp>
#include "defintions.hpp"

#include "Window.hpp"

class Engine
{
private:
	Window m_window;
public:
	void Init();
	void Loop();
	void Fini();
};

