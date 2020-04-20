#include "Game.hpp"

void Game::Init(VulkanDevice& device, Window& window)
{
	m_device = device;
	m_window = window;

	LOG_F(INFO, "GAME INIT");

	m_gameRoot.hInput.create<InputKeyboard>();
	m_gameRoot.hInput.create<InputMouse>();

	ModuleInfo<Texture2D> texturePlanks = m_gameRoot.hTexture.create2D("textures//Planks12_col.jpg");
	ModuleInfo<Texture2D> texturePlanksNM = m_gameRoot.hTexture.create2D("textures//Planks12_nrm.jpg");

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

	ModuleInfo<ModuleMaterial> greenMaterial = m_gameRoot.hMaterial.create();
	greenMaterial->setDiffuseColor(Vec4(0.f, 1.f, 0.0, 1.f));
	greenMaterial->setAmbientColor(Vec4(1.f, 1.f, 1.f, 1.f));
	greenMaterial->setAmbientStrength(0.1f);
	m_gameRoot.hMaterial.addAlias(greenMaterial.ID, "green");

	ModuleInfo<ModuleMaterial> redMaterial = m_gameRoot.hMaterial.create();
	redMaterial->setDiffuseColor(Vec4(1.f, 0.f, 0.0, 1.f));
	redMaterial->setAmbientColor(Vec4(1.f, 1.f, 1.f, 1.f));
	redMaterial->setSpecularColor(Vec4(1.f, 1.f, 1.f, 1.f));
	redMaterial->setAmbientStrength(0.1f);
	redMaterial->setSpecularStrength(1.0f);
	m_gameRoot.hMaterial.addAlias(redMaterial.ID, "red");

	ModuleInfo<GeoCube> geoCube = m_gameRoot.hGeometry.create<GeoCube>();
	m_gameRoot.hGeometry.addAlias(geoCube.ID, "cube");

	ModuleInfo<GeoPlane> geoPlane = m_gameRoot.hGeometry.create<GeoPlane>();
	m_gameRoot.hGeometry.addAlias(geoPlane.ID, "plane");

	ModuleInfo<GeoWavefront> geoApe = m_gameRoot.hGeometry.create<GeoWavefront>("assets/suzanne.obj");
	m_gameRoot.hGeometry.addAlias(geoApe.ID, "ape");

	ModuleInfo<GeoWavefront> geoSphere = m_gameRoot.hGeometry.create<GeoWavefront>("assets/sphere.obj");
	m_gameRoot.hGeometry.addAlias(geoSphere.ID, "sphere");

	ModuleInfo<TextureCubemap> skyboxTexture = m_gameRoot.hTexture.createCubemap("textures/sky", "jpg");
	ModuleInfo<Skybox> skybox = m_gameRoot.hSkybox.create(skyboxTexture.ID, geoCube.ID);
	m_gameRoot.hSkybox.addAlias(skybox.ID, "bluesky");

	m_activeDemo = std::make_unique<DemoBlueUniverse>();
	m_activeDemo->init(m_gameRoot);
	m_activeDemo->run(m_gameRoot);

	HandlerEvent::instance().registerEvent("keyPress", [this](Event& event) {
		this->onKeyPress(reinterpret_cast<EventKeyPress&>(event));
	});

	////ModuleInfo<ModuleGeometry> test = m_gameRoot.hGeometry.create<ModuleGeometry>();

	////ModuleGeometry* test2 = m_gameRoot.hGeometry.get<ModuleGeometry>(test.ID);

	//{ //Test Texture

	//}

	//{//Test Event
	//	HandlerEvent& eventHandler = HandlerEvent::instance();
	//	eventHandler.registerEvent("test", [this](Event& event) {
	//		this->Test(reinterpret_cast<EventKeyPress&>(event));
	//	});

	//	EventKeyPress myEvent(0, 0, 0, 0);
	//	eventHandler.notify("test", myEvent);
	//}

	//ModuleInfo<Scene> scene = m_gameRoot.hScene.create();
	//m_gameRoot.m_mainScene = scene.ID;
	//ModuleInfo<SceneNode> rootNode = m_gameRoot.hSceneNode.create();
	//scene->addRootNode(rootNode.ID);

	//{//Test Camera
	//	ModuleInfo<Camera> camera = m_gameRoot.hCamera.create();
	//	camera->setPosition(Vec3(50, 10, 20), 0, 0);
	//	camera->setPerspective(45, SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.01f, 1000.f);
	//	scene->m_activeCamera = camera.ID;
	//}

	//{ //Plane
	//	ModuleInfo<GameObjekt> go = m_gameRoot.hGameObject.create();
	//	ModuleInfo<GeoCube> geoCube = m_gameRoot.hGeometry.create<GeoCube>();
	//	ModuleInfo<ModuleTransformation> transform = m_gameRoot.hTransformation.create();
	//	ModuleInfo<ModuleMaterial> material = m_gameRoot.hMaterial.create();


	//	go->addModule<ModuleGeometry>(geoCube.ID);
	//	go->addModule<ModuleTransformation>(transform.ID);
	//	go->addModule<ModuleMaterial>(material.ID);

	//	rootNode->addGameObject(go.ID);

	//	transform->scaleAbsolute(500.f, 0.01f, 500.f);

	//	material->setDiffuseColor(Vec4(67/255.0f, 230/255.0f, 63/255.f, 1));
	//	material->setAmbientColor(Vec4(1.f, 1.f, 1.f, 1.f));
	//	material->setAmbientStrength(0.2f);
	//}

	//{ //Wavefront Test
	//	ModuleInfo<GameObjekt> go = m_gameRoot.hGameObject.create();
	//	ModuleInfo<GeoWavefront> geo = m_gameRoot.hGeometry.create<GeoWavefront>("assets/suzanne.obj");
	//	ModuleInfo<ModuleTransformation> transform = m_gameRoot.hTransformation.create();
	//	ModuleInfo<ModuleMaterial> material = m_gameRoot.hMaterial.create();

	//	m_gameRoot.hGameObject.addAlias(go.ID, "sun");

	//	material->setDiffuseColor(Vec4(1.f, 0, 0, 1));

	//	go->addModule<ModuleGeometry>(geo.ID);
	//	go->addModule<ModuleTransformation>(transform.ID);
	//	go->addModule <ModuleMaterial>(material.ID);

	//	rootNode->addGameObject(go.ID);

	//	//transform->translate(0, 20, 0);
	//}

	//{ //Wavefront Test
	//	ModuleInfo<GameObjekt> go = m_gameRoot.hGameObject.create();
	//	ModuleInfo<GeoWavefront> geo = m_gameRoot.hGeometry.create<GeoWavefront>("assets/suzanne.obj");
	//	ModuleInfo<ModuleTransformation> transform = m_gameRoot.hTransformation.create();
	//	ModuleInfo<ModuleMaterial> material = m_gameRoot.hMaterial.create();

	//	m_gameRoot.hGameObject.addAlias(go.ID, "earth");

	//	material->setDiffuseColor(Vec4(1.f, 0, 0, 1));

	//	go->addModule<ModuleGeometry>(geo.ID);
	//	go->addModule<ModuleTransformation>(transform.ID);
	//	go->addModule <ModuleMaterial>(material.ID);

	//	rootNode->addGameObject(go.ID);

	//	//transform->translate(0, 20, 0);
	//}

	//{
	//	ModuleInfo<SceneNode> sun = m_gameRoot.hSceneNode.create();
	//	ModuleInfo<SceneNode> earth = m_gameRoot.hSceneNode.create();
	//	ModuleInfo<SceneNode> earth2 = m_gameRoot.hSceneNode.create();
	//	ModuleInfo<SceneNode> moon = m_gameRoot.hSceneNode.create();

	//	ModuleInfo<ModuleTransformation> sunTrans = m_gameRoot.hTransformation.create();
	//	ModuleInfo<ModuleTransformation> earthTrans = m_gameRoot.hTransformation.create();
	//	ModuleInfo<ModuleTransformation> earthRot = m_gameRoot.hTransformation.create();
	//	ModuleInfo<ModuleTransformation> moonTrans = m_gameRoot.hTransformation.create();

	//	m_gameRoot.hTransformation.addAlias(earthRot.ID, "earthRot");

	//	earthTrans->translateX(20);
	//	earthRot->rotateX(0.001f);

	//	sun->setTransformationID(sunTrans.ID);
	//	sun->addChild(earth.ID);
	//	sun->addGameObject(m_gameRoot.hGameObject.getID("sun"));

	//	earth->setTransformationID(earthRot.ID);
	//	earth->addChild(earth2.ID);
	//	
	//	earth2->setTransformationID(earthTrans.ID);
	//	earth2->addGameObject(m_gameRoot.hGameObject.getID("earth"));

	//	Scene* scene = m_gameRoot.hScene.get(m_gameRoot.m_mainScene);
	//	scene->addRootNode(sun.ID);
	//}




	//{ //Wavefront Test
	//	ModuleInfo<GameObjekt> go = m_gameRoot.hGameObject.create();
	//	ModuleInfo<GeoWavefront> geo = m_gameRoot.hGeometry.create<GeoWavefront>("assets/suzanne.obj");
	//	ModuleInfo<ModuleTransformation> transform = m_gameRoot.hTransformation.create();
	//	ModuleInfo<ModuleMaterial> material = m_gameRoot.hMaterial.create();

	//	material->setDiffuseColor(Vec4(1.f, 0, 0, 1));

	//	go->addModule<ModuleGeometry>(geo.ID);
	//	go->addModule<ModuleTransformation>(transform.ID);
	//	go->addModule <ModuleMaterial>(material.ID);

	//	transform->translate(0, 20, 0);

	//	rootNode->addGameObject(go.ID);

	//}

	//{//Test Skybox
	//	ModuleInfo<TextureCubemap> skyboxTexture = m_gameRoot.hTexture.createCubemap("textures/sky", "jpg");
	//	ModuleInfo<GeoCube> geoCube = m_gameRoot.hGeometry.create<GeoCube>();
	//	ModuleInfo<Skybox> geoSkybox = m_gameRoot.hSkybox.create(skyboxTexture.ID, geoCube.ID);
	//}


	//{//Portal Wall #1
	//	ModuleInfo<GameObjekt> go = m_gameRoot.hGameObject.create();
	//	ModuleInfo<GeoCube> geo = m_gameRoot.hGeometry.create<GeoCube>();
	//	ModuleInfo<ModuleTransformation> transform = m_gameRoot.hTransformation.create();


	//	go->addModule<ModuleGeometry>(geo.ID);
	//	go->addModule<ModuleTransformation>(transform.ID);
	//	go->addModule <ModuleMaterial>(m_gameRoot.hMaterial.getID("orange"));

	//	transform->translate(20, 10, 0);
	//	transform->scaleAbsolute(20, 20, 1);

	//	rootNode->addGameObject(go.ID);

	//}

	//{//Portal Wall #2
	//	ModuleInfo<GameObjekt> go = m_gameRoot.hGameObject.create();
	//	ModuleInfo<GeoCube> geo = m_gameRoot.hGeometry.create<GeoCube>();
	//	ModuleInfo<ModuleTransformation> transform = m_gameRoot.hTransformation.create();


	//	go->addModule<ModuleGeometry>(geo.ID);
	//	go->addModule<ModuleTransformation>(transform.ID);
	//	go->addModule <ModuleMaterial>(m_gameRoot.hMaterial.getID("blue"));

	//	transform->translate(-20, 10, 0);
	//	transform->scaleAbsolute(20, 20, 1);

	//	rootNode->addGameObject(go.ID);
	//}

	//{//Occlusion Wall #1
	//	ModuleInfo<GameObjekt> go = m_gameRoot.hGameObject.create();
	//	ModuleInfo<GeoCube> geo = m_gameRoot.hGeometry.create<GeoCube>();
	//	ModuleInfo<ModuleTransformation> transform = m_gameRoot.hTransformation.create();


	//	go->addModule<ModuleGeometry>(geo.ID);
	//	go->addModule<ModuleTransformation>(transform.ID);
	//	go->addModule <ModuleMaterial>(m_gameRoot.hMaterial.getID("default"));

	//	transform->translate(-20, 10, 10);
	//	transform->scaleAbsolute(20, 20, 1);

	//	rootNode->addGameObject(go.ID);
	//}

	//{
	//	//Portal #1
	//	ModuleInfo<GameObjekt> go = m_gameRoot.hGameObject.create();
	//	ModuleInfo<GeoPlane> geo = m_gameRoot.hGeometry.create<GeoPlane>();
	//	ModuleInfo<ModuleTransformation> transform = m_gameRoot.hTransformation.create();
	//	ModuleInfo<ModulePortal> portal = m_gameRoot.hPortal.create();

	//	go->addModule<ModuleGeometry>(geo.ID);
	//	go->addModule<ModuleTransformation>(transform.ID);
	//	go->addModule <ModuleMaterial>(m_gameRoot.hMaterial.getID("default"));
	//	go->addModule<ModulePortal>(portal.ID);

	//	transform->translate(20, 5, 0.1f);
	//	transform->scaleAbsolute(10, 10, 1);

	//	rootNode->addGameObject(go.ID);
	//}

	//{
	//	//Portal #2
	//	ModuleInfo<GameObjekt> go = m_gameRoot.hGameObject.create();
	//	ModuleInfo<GeoPlane> geo = m_gameRoot.hGeometry.create<GeoPlane>();
	//	ModuleInfo<ModuleTransformation> transform = m_gameRoot.hTransformation.create();
	//	ModuleInfo<ModulePortal> portal = m_gameRoot.hPortal.create();


	//	go->addModule<ModuleGeometry>(geo.ID);
	//	go->addModule<ModuleTransformation>(transform.ID);
	//	go->addModule <ModuleMaterial>(m_gameRoot.hMaterial.getID("default"));
	//	go->addModule<ModulePortal>(portal.ID);
	//	transform->translate(-20, 5, 0.1f);
	//	transform->scaleAbsolute(10, 10, 1);

	//	rootNode->addGameObject(go.ID);
	//}


	m_gameRoot.Init(m_device);
	m_renderer.Init(m_device, m_gameRoot);

}

void Game::Tick()
{

	/*ModuleTransformation* earthRot = m_gameRoot.hTransformation.get(
		m_gameRoot.hTransformation.getID("earthRot")
	);

	earthRot->rotateY(0.003f);*/

	m_activeDemo->update(0, m_gameRoot);

	//Traverse SceneGraph and update local/global matrix
	for (const int32_t sceneID : m_gameRoot.m_activeScenes) {
		Scene* scene = m_gameRoot.hScene.get(sceneID);
		for (const int32_t rootNodeID : scene->getRootNodes()) {
			SceneNode* rootNode = m_gameRoot.hSceneNode.get(rootNodeID);
			Mat4 globalMat(1.0f);
			rootNode->traverse2(m_gameRoot, rootNode, globalMat);
		}
	}
	

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

void Game::onKeyPress(EventKeyPress& event)
{
	if (event.action != GLFW_PRESS) {
		return;
	}
	if (event.key == GLFW_KEY_1) {
		m_activeDemo = std::make_unique<DemoBlueUniverse>();
		m_activeDemo->init(m_gameRoot);
		m_activeDemo->run(m_gameRoot);
	}
	else if (event.key == GLFW_KEY_2) {
		m_activeDemo = std::make_unique<DemoBlue>();
		m_activeDemo->init(m_gameRoot);
		m_activeDemo->run(m_gameRoot);
	}
	else if (event.key == GLFW_KEY_3) {
		m_activeDemo = std::make_unique<DemoMaterial>();
		m_activeDemo->init(m_gameRoot);
		m_activeDemo->run(m_gameRoot);
	}
}
