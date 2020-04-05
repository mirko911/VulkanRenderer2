#pragma once
#include <loguru.hpp>

#include "GameRoot.hpp"
#include "Handler/HandlerGeometry.hpp"
#include "Modules/ModuleGeometry.hpp"
class Game
{
private:
	GameRoot m_gameRoot;
public:
	void Init();
	void Tick();
	void Draw();
	void Fini();
};

