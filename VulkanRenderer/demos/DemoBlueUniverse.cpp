#include "DemoBlueUniverse.hpp"

void DemoBlueUniverse::initBlueWorld(GameRoot& gameRoot)
{
	//Setup camera
	ModuleInfo<Camera> camera = gameRoot.hCamera.create();
	camera->setPosition(Vec3(50, 10, 20), 0, 180);
	camera->setPerspective(45, SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.01f, 10000.0f);

	//Setup scene and root node
	ModuleInfo<Scene> scene = gameRoot.hScene.create();
	ModuleInfo<SceneNode> rootNode = gameRoot.hSceneNode.create();

	mainScene = scene.ID;
	scenes.push_back(scene.ID);
	scene->addRootNode(rootNode.ID);
	scene->m_activeCamera = camera.ID;
	sceneBlueSky = scene.ID;

	{  //Green Plane
		ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
		ModuleInfo<ModuleTransformation> transformation = gameRoot.hTransformation.create();

		transformation->scaleAbsolute(500.0f, 0.01f, 500.0f);

		go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("cube"));
		go->addModule<ModuleTransformation>(transformation.ID);
		go->addModule<ModuleMaterial>(gameRoot.hMaterial.getID("green"));

		rootNode->addGameObject(go.ID);
	}

	{ //Orange Portal Wall
		ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
		ModuleInfo<ModuleTransformation> transformation = gameRoot.hTransformation.create();

		transformation->scaleAbsolute(20, 20, 1.0f);
		transformation->translateAbsolute(10, 10, 0);

		go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("cube"));
		go->addModule<ModuleTransformation>(transformation.ID);
		go->addModule<ModuleMaterial>(gameRoot.hMaterial.getID("orange"));

		rootNode->addGameObject(go.ID);
	}

	{ //Blue Portal Wall
		ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
		ModuleInfo<ModuleTransformation> transformation = gameRoot.hTransformation.create();

		transformation->scaleAbsolute(20, 20, 1.0f);
		transformation->translateAbsolute(50, 10, 0);

		go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("cube"));
		go->addModule<ModuleTransformation>(transformation.ID);
		go->addModule<ModuleMaterial>(gameRoot.hMaterial.getID("blue"));

		rootNode->addGameObject(go.ID);
	}

	{ //Red Ape
		ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
		ModuleInfo<ModuleTransformation> transformation = gameRoot.hTransformation.create();

		transformation->scaleAbsolute(5, 5, 5);
		transformation->translateAbsolute(10, 10, 30);

		go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("ape"));
		go->addModule<ModuleTransformation>(transformation.ID);
		go->addModule<ModuleMaterial>(gameRoot.hMaterial.getID("red"));

		rootNode->addGameObject(go.ID);
	}

	{
		//Setup Portal
		ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
		ModuleInfo<ModuleTransformation> transformation = gameRoot.hTransformation.create();
		ModuleInfo<ModulePortal> portal = gameRoot.hPortal.create();

		go->addModule<ModuleTransformation>(transformation.ID);
		go->addModule<ModulePortal>(portal.ID);
		go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("plane"));

		portal->setStartGameObject(go.ID);

		rootNode->addGameObject(go.ID);

		transformation->scaleAbsolute(10, 10, 1);
		transformation->translateAbsolute(10, 10, 1);

		portalStart = portal.ID;
	}
}

void DemoBlueUniverse::initUniverse(GameRoot& gameRoot)
{
	//Setup materials
	ModuleInfo<Texture2D> sunTexture = gameRoot.hTexture.create2D("textures//2k_sun.jpg");
	ModuleInfo<Texture2D> earthTexture = gameRoot.hTexture.create2D("textures//2k_earth_daymap.jpg");
	ModuleInfo<Texture2D> earthNMTexture = gameRoot.hTexture.create2D("textures//2k_earth_normal_map.jpg");
	ModuleInfo<Texture2D> moonTexture = gameRoot.hTexture.create2D("textures//2k_moon.jpg");
	ModuleInfo<ModuleMaterial> sunMaterial = gameRoot.hMaterial.create();
	ModuleInfo<ModuleMaterial> earthMaterial = gameRoot.hMaterial.create();
	ModuleInfo<ModuleMaterial> moonMaterial = gameRoot.hMaterial.create();

	sunMaterial->setDiffuseColor(Vec4(1, 1, 0, 0));
	sunMaterial->setAmbientColor(Vec4(1.0f));
	sunMaterial->setAmbientStrength(1);
	sunMaterial->setTextureID(sunTexture.ID);

	earthMaterial->setDiffuseColor(Vec4(1, 1, 1, 1));
	earthMaterial->setAmbientColor(Vec4(1.0f));
	earthMaterial->setAmbientStrength(0.5);
	earthMaterial->setTextureID(earthTexture.ID);
	earthMaterial->setNormalMapID(earthNMTexture.ID);
	
	moonMaterial->setDiffuseColor(Vec4(0.9, 0.9, 0.9, 1.0f));
	moonMaterial->setTextureID(moonTexture.ID);

	//Setup camera
	ModuleInfo<Camera> camera = gameRoot.hCamera.create();
	camera->setPosition(Vec3(50, 10, 20), 0, 180);
	camera->setPerspective(45, SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.01f, 10000.0f);

	//Setup scene and root node
	ModuleInfo<Scene> scene = gameRoot.hScene.create();
	ModuleInfo<SceneNode> rootNode = gameRoot.hSceneNode.create();

	scenes.push_back(scene.ID);
	scene->addRootNode(rootNode.ID);
	scene->m_activeCamera = camera.ID;
	sceneUniverse = scene.ID;


	{ 
		ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
		ModuleInfo<ModuleTransformation> transformation = gameRoot.hTransformation.create();

		go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("sphere"));
		go->addModule<ModuleTransformation>(transformation.ID);
		go->addModule<ModuleMaterial>(sunMaterial.ID);

		transformation->scale(Vec3(10, 10, 10));
		sunRotation = transformation.ID;

		rootNode->addGameObject(go.ID);
	}
	{
		ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
		ModuleInfo<ModuleTransformation> transformation = gameRoot.hTransformation.create(); //earth own rotation
		ModuleInfo<SceneNode> node = gameRoot.hSceneNode.create();
		ModuleInfo<ModuleTransformation> sceneNodeTransform = gameRoot.hTransformation.create(); //orbital rotation
		ModuleInfo<SceneNode> node1 = gameRoot.hSceneNode.create();
		ModuleInfo<ModuleTransformation> sceneNodeTransform1 = gameRoot.hTransformation.create(); //orbital rotation
		
		go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("sphere"));
		go->addModule<ModuleTransformation>(transformation.ID);
		go->addModule<ModuleMaterial>(earthMaterial.ID);

		earthRotation = sceneNodeTransform.ID;

		sceneNodeTransform1->translateY(30);

		earthOwnRotation = transformation.ID;

		node->setTransformationID(sceneNodeTransform.ID);
		node->addChild(node1.ID);
		node1->setTransformationID(sceneNodeTransform1.ID);
		node1->addGameObject(go.ID);

		rootNode->addChild(node.ID);
	}
	{
		ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
		ModuleInfo<ModuleTransformation> transformation = gameRoot.hTransformation.create();

		go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("sphere"));
		go->addModule<ModuleTransformation>(transformation.ID);
		go->addModule<ModuleMaterial>(moonMaterial.ID);

		sunRotation = transformation.ID;

		rootNode->addGameObject(go.ID);
	}

	{
		//Setup Portal
		ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
		ModuleInfo<ModuleTransformation> transformation = gameRoot.hTransformation.create();
		ModuleInfo<ModulePortal> portal = gameRoot.hPortal.create();

		go->addModule<ModuleTransformation>(transformation.ID);
		go->addModule<ModulePortal>(portal.ID);
		go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("plane"));

		rootNode->addGameObject(go.ID);

		portal->setStartGameObject(go.ID);

		portalEnd = portal.ID;
	}
}

void DemoBlueUniverse::init(GameRoot& gameRoot)
{
	initBlueWorld(gameRoot);
	initUniverse(gameRoot);

	ModulePortal* startPortal = gameRoot.hPortal.get(portalStart);
	ModulePortal* endPortal = gameRoot.hPortal.get(portalEnd);

	startPortal->setDestinatioNGameObject(endPortal->getStartGameObject());
	endPortal->setDestinatioNGameObject(startPortal->getStartGameObject());
}

void DemoBlueUniverse::run(GameRoot& gameRoot)
{
	gameRoot.m_mainScene = mainScene;
	gameRoot.m_activeScenes = scenes;
}

void DemoBlueUniverse::update(const float fTimeDelta, GameRoot& gameRoot)
{
}
