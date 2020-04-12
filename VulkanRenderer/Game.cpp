#include "Game.hpp"

void Game::Init(VulkanDevice& device, Window& window)
{
	m_device = device;
	m_window = window;

	LOG_F(INFO, "GAME INIT");

	m_gameRoot.hInput.create<InputKeyboard>();
	m_gameRoot.hInput.create<InputMouse>();

	ModuleInfo<ModuleMaterial> defaultMaterial = m_gameRoot.hMaterial.create();
	defaultMaterial->setAmbientColor(Vec4(1, 1, 1, 1));
	defaultMaterial->setDiffuseColor(Vec4(0.5f, 0.5, 0.5f, 1));
	defaultMaterial->setSpecularColor(Vec4(235, 242, 242, 1));
	defaultMaterial->setAmbientStrength(0.2f);
	defaultMaterial->setSpecularStrength(0.32f);
	defaultMaterial->setTextureID(0);
	defaultMaterial->setNormalMapID(1);

	ModuleInfo<ModuleMaterial> orangeMaterial = m_gameRoot.hMaterial.create();
	orangeMaterial->setDiffuseColor(Vec4(1.f, 0.501f, 0.313f, 1.f));
	orangeMaterial->setAmbientColor(Vec4(1.f, 1.f, 1.f, 1.f));
	orangeMaterial->setAmbientStrength(0.0f);
	m_gameRoot.hMaterial.addAlias(orangeMaterial.ID, "orange");

	ModuleInfo<ModuleMaterial> blueMaterial = m_gameRoot.hMaterial.create();
	blueMaterial->setDiffuseColor(Vec4(0.f, 0.f, 1.0, 1.f));
	blueMaterial->setAmbientColor(Vec4(1.f, 1.f, 1.f, 1.f));
	blueMaterial->setAmbientStrength(0.1f);
	m_gameRoot.hMaterial.addAlias(blueMaterial.ID, "blue");
	
	//ModuleInfo<ModuleGeometry> test = m_gameRoot.hGeometry.create<ModuleGeometry>();

	//ModuleGeometry* test2 = m_gameRoot.hGeometry.get<ModuleGeometry>(test.ID);

	{ //Test Gameobject
		ModuleInfo<GameObjekt> go = m_gameRoot.hGameObject.create();
		ModuleInfo<GeoCube> geoCube = m_gameRoot.hGeometry.create<GeoCube>();
		ModuleInfo<ModuleTransformation> transform = m_gameRoot.hTransformation.create();

		transform->translateAbsolute(50.f, 50.f, 50.f);

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

	ModuleInfo<Scene> scene = m_gameRoot.hScene.create();

	{//Test Camera
		ModuleInfo<Camera> camera = m_gameRoot.hCamera.create();
		camera->setPosition(Vec3(50, 10, 20), 0, 0);
		camera->setPerspective(45, SCREEN_WIDTH / SCREEN_HEIGHT, 0.01f, 1000.f);
		scene->m_activeCamera = camera.ID;
	}

	{ //Plane
		ModuleInfo<GameObjekt> go = m_gameRoot.hGameObject.create();
		ModuleInfo<GeoCube> geoCube = m_gameRoot.hGeometry.create<GeoCube>();
		ModuleInfo<ModuleTransformation> transform = m_gameRoot.hTransformation.create();
		ModuleInfo<ModuleMaterial> material = m_gameRoot.hMaterial.create();

		go->addModule<ModuleGeometry>(geoCube.ID);
		go->addModule<ModuleTransformation>(transform.ID);
		go->addModule<ModuleMaterial>(material.ID);

		transform->scaleAbsolute(500.f, 0.01f, 500.f);

		material->setDiffuseColor(Vec4(67/255.0f, 230/255.0f, 63/255.f, 1));
		material->setAmbientColor(Vec4(1.f, 1.f, 1.f, 1.f));
		material->setAmbientStrength(0.2f);
	}

	{ //Wavefront Test
		ModuleInfo<GameObjekt> go = m_gameRoot.hGameObject.create();
		ModuleInfo<GeoWavefront> geo = m_gameRoot.hGeometry.create<GeoWavefront>("assets/suzanne.obj");
		ModuleInfo<ModuleTransformation> transform = m_gameRoot.hTransformation.create();
		ModuleInfo<ModuleMaterial> material = m_gameRoot.hMaterial.create();

		material->setDiffuseColor(Vec4(1.f, 0, 0, 1));

		go->addModule<ModuleGeometry>(geo.ID);
		go->addModule<ModuleTransformation>(transform.ID);
		go->addModule <ModuleMaterial>(material.ID);

		transform->translate(0, 20, 0);
	}

	{//Test Skybox
		ModuleInfo<TextureCubemap> skyboxTexture = m_gameRoot.hTexture.createCubemap("textures/sky", "jpg");
		ModuleInfo<GeoCube> geoCube = m_gameRoot.hGeometry.create<GeoCube>();
		ModuleInfo<Skybox> geoSkybox = m_gameRoot.hSkybox.create(skyboxTexture.ID, geoCube.ID);
	}


	{//Portal Wall #1
		ModuleInfo<GameObjekt> go = m_gameRoot.hGameObject.create();
		ModuleInfo<GeoCube> geo = m_gameRoot.hGeometry.create<GeoCube>();
		ModuleInfo<ModuleTransformation> transform = m_gameRoot.hTransformation.create();


		go->addModule<ModuleGeometry>(geo.ID);
		go->addModule<ModuleTransformation>(transform.ID);
		go->addModule <ModuleMaterial>(m_gameRoot.hMaterial.getID("orange"));

		transform->translate(30, 10, 0);
		transform->scaleAbsolute(20, 20, 1);
	}

	{//Portal Wall #2
		ModuleInfo<GameObjekt> go = m_gameRoot.hGameObject.create();
		ModuleInfo<GeoCube> geo = m_gameRoot.hGeometry.create<GeoCube>();
		ModuleInfo<ModuleTransformation> transform = m_gameRoot.hTransformation.create();


		go->addModule<ModuleGeometry>(geo.ID);
		go->addModule<ModuleTransformation>(transform.ID);
		go->addModule <ModuleMaterial>(m_gameRoot.hMaterial.getID("blue"));

		transform->translate(-30, 10, 0);
		transform->scaleAbsolute(20, 20, 1);

	}


	m_gameRoot.Init(m_device);
	m_renderer.Init(m_device, m_gameRoot);
}

void Game::Tick()
{
//	LOG_F(INFO, "GAME TICK");
	m_gameRoot.update(0);
}

void Game::Draw()
{
	m_renderer.Render(m_gameRoot);
//	LOG_F(INFO, "GAME DRAW");

}

void Game::Fini()
{
	m_renderer.Destroy();
	LOG_F(INFO, "GAME FINI");

}
