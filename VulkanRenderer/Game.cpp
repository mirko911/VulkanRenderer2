#include "Game.hpp"

void Game::Init(VulkanDevice& device, Window& window)
{
	m_device = device;
	m_window = window;

	LOG_F(INFO, "GAME INIT");

	m_gameRoot.hInput.create<InputKeyboard>();
	m_gameRoot.hInput.create<InputMouse>();
	
	//ModuleInfo<ModuleGeometry> test = m_gameRoot.hGeometry.create<ModuleGeometry>();

	//ModuleGeometry* test2 = m_gameRoot.hGeometry.get<ModuleGeometry>(test.ID);

	{ //Test Gameobject
		ModuleInfo<GameObjekt> go = m_gameRoot.hGameObject.create();
		ModuleInfo<GeoCube> geoCube = m_gameRoot.hGeometry.create<GeoCube>();
		ModuleInfo<ModuleTransformation> transform = m_gameRoot.hTransformation.create();

		go->addModule<ModuleGeometry>(geoCube.ID);
		go->addModule<ModuleTransformation>(transform.ID);
	}

	{ //Test Texture
		ModuleInfo<Texture2D> texturePlanks = m_gameRoot.hTexture.create2D("textures//Planks12_col.jpg");
		ModuleInfo<Texture2D> texturePlanksNM = m_gameRoot.hTexture.create2D("textures//Planks12_nrm.jpg");
	}

	{//Test Event
		HandlerEvent& eventHandler = HandlerEvent::instance();
		eventHandler.registerEvent("test", [this](Event& event) {
			this->Test(reinterpret_cast<EventKeyPress&>(event));
		});

		EventKeyPress myEvent(0, 0, 0, 0);
		eventHandler.notify("test", myEvent);
	}

	m_renderer.Init(m_device, m_gameRoot);
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
