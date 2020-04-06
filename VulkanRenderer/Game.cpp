#include "Game.hpp"

void Game::Init()
{
	LOG_F(INFO, "GAME INIT");

	HandlerGeometry geoHandler;
	ModuleInfo<ModuleGeometry> test = m_gameRoot.hGeometry.create<ModuleGeometry>();

	ModuleGeometry* test2 = m_gameRoot.hGeometry.get<ModuleGeometry>(test.ID);


}

void Game::Tick()
{
	LOG_F(INFO, "GAME TICK");

}

void Game::Draw()
{
	LOG_F(INFO, "GAME DRAW");

}

void Game::Fini()
{
	LOG_F(INFO, "GAME FINI");

}
