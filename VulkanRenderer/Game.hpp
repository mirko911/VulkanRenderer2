#pragma once
#include <loguru.hpp>

#include "GameRoot.hpp"
#include "GeoCube.hpp"
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

