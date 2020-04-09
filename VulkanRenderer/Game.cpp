#include "Game.hpp"

void Game::Init(VulkanDevice& device, Window& window)
{
	m_device = device;
	m_window = window;

	LOG_F(INFO, "GAME INIT");

	
	//ModuleInfo<ModuleGeometry> test = m_gameRoot.hGeometry.create<ModuleGeometry>();

	//ModuleGeometry* test2 = m_gameRoot.hGeometry.get<ModuleGeometry>(test.ID);

	{ //Test Gameobject
		ModuleInfo<GameObjekt> go = m_gameRoot.hGameObject.create();
		ModuleInfo<GeoCube> geoCube = m_gameRoot.hGeometry.create<GeoCube>();
		ModuleInfo<ModuleTransformation> transform = m_gameRoot.hTransformation.create();

		go->addModule<ModuleGeometry>(geoCube.ID);
		go->addModule<ModuleTransformation>(transform.ID);
	}

	m_renderer.Init(m_device);
}

void Game::Tick()
{
//	LOG_F(INFO, "GAME TICK");

}

void Game::Draw()
{
	m_renderer.Render();
//	LOG_F(INFO, "GAME DRAW");

}

void Game::Fini()
{
	m_renderer.Destroy();
	LOG_F(INFO, "GAME FINI");

}
