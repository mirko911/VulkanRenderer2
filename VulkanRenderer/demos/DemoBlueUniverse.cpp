#include "DemoBlueUniverse.hpp"

void DemoBlueUniverse::initBlueWorld(GameRoot& gameRoot)
{
	//Setup camera
	ModuleInfo<Camera> camera = gameRoot.hCamera.create();
	camera->setPosition(Vec3(50, 10, 20), 0, 180);
	camera->setPerspective(45, SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.01f, 10000.0f);
	camera->setStatic(false);

	//Setup scene and root node
	ModuleInfo<Scene> scene = gameRoot.hScene.create();
	ModuleInfo<SceneNode> rootNode = gameRoot.hSceneNode.create();

	mainScene = scene.ID;
	scenes.push_back(scene.ID);
	scene->addRootNode(rootNode.ID);
	scene->m_activeCamera = camera.ID;
	scene->m_skyboxID = gameRoot.hSkybox.getID("bluesky");

	sceneBlueSky = scene.ID;

	{  //Green Plane
		ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
		ModuleInfo<ModuleTransformation> transformation = gameRoot.hTransformation.create();

		transformation->scaleAbsolute(500.0f, 0.01f, 500.0f);

		go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("cube"));
		go->addModule<ModuleTransformation>(transformation.ID);
		go->addModule<ModuleMaterial>(gameRoot.hMaterial.getID("green"));
		go->setSceneID(scene.ID);

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
		go->setSceneID(scene.ID);

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
		go->setSceneID(scene.ID);

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
		go->setSceneID(scene.ID);

		rootNode->addGameObject(go.ID);
	}

	//{//Occlusion Wall #1
	//	ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
	//	ModuleInfo<ModuleTransformation> transform = gameRoot.hTransformation.create();


	//	go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("cube"));
	//	go->addModule<ModuleTransformation>(transform.ID);
	//	go->addModule <ModuleMaterial>(gameRoot.hMaterial.getID("default"));
	//	go->setSceneID(scene.ID);

	//	transform->translate(10, 10, 10);
	//	transform->scaleAbsolute(20, 20, 1);

	//	rootNode->addGameObject(go.ID);
	//}

	{
		//Setup Portal
		ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
		ModuleInfo<ModuleTransformation> transformation = gameRoot.hTransformation.create();
		ModuleInfo<ModulePortal> portal = gameRoot.hPortal.create();

		go->addModule<ModuleTransformation>(transformation.ID);
		go->addModule<ModulePortal>(portal.ID);
		go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("plane"));
		go->setSceneID(scene.ID);

		portal->setStartGameObject(go.ID);

		rootNode->addGameObject(go.ID);

		transformation->scaleAbsolute(10, 10, 1);
		transformation->translateAbsolute(10, 10, 1);

		portalStart = portal.ID;
	}
}

void DemoBlueUniverse::initUniverse(GameRoot& gameRoot)
{
	ModuleInfo<TextureCubemap> skyboxTexture = gameRoot.hTexture.createCubemap("textures//universe_skybox//skybox", "jpg");
	ModuleInfo<Skybox> skybox = gameRoot.hSkybox.create(skyboxTexture.ID, gameRoot.hGeometry.getID("cube"));


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
	scene->m_skyboxID = skybox.ID;
	sceneUniverse = scene.ID;
	//mainScene = scene.ID;

	{ 
		ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
		ModuleInfo<ModuleTransformation> transformation = gameRoot.hTransformation.create();

		go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("sphere"));
		go->addModule<ModuleTransformation>(transformation.ID);
		go->addModule<ModuleMaterial>(sunMaterial.ID);
		go->setSceneID(scene.ID);

		transformation->scale(Vec3(20, 20, 20));
		sunRotation = transformation.ID;

		rootNode->addGameObject(go.ID);
	}
	{
		//-rootNode
			// # goSUN
				// # scale 20,20,20
				// # rotate y
			// - node
				//# translate 10
				// - node
					//# rotate
					//# GO Earth
						//scale 
						//rotate
					// - node
						// translate 4
						//-node
							//rotate
							//GO Moon
								//scale
								//rotate

		ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
		ModuleInfo<ModuleTransformation> transformation = gameRoot.hTransformation.create(); //earth own rotation
		ModuleInfo<SceneNode> node = gameRoot.hSceneNode.create();
		ModuleInfo<ModuleTransformation> sceneNodeTransform = gameRoot.hTransformation.create(); //orbital rotation
		ModuleInfo<SceneNode> node1 = gameRoot.hSceneNode.create();
		ModuleInfo<ModuleTransformation> sceneNodeTransform1 = gameRoot.hTransformation.create(); //orbital rotation
		
		go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("sphere"));
		go->addModule<ModuleTransformation>(transformation.ID);
		go->addModule<ModuleMaterial>(earthMaterial.ID);
		go->setSceneID(scene.ID);

		transformation->scaleAbsolute(Vec3(7));

		earthRotation = sceneNodeTransform.ID;

		sceneNodeTransform1->translateY(15);

		earthOwnRotation = transformation.ID;

		node->setTransformationID(sceneNodeTransform.ID);
		node->addChild(node1.ID);
		node1->setTransformationID(sceneNodeTransform1.ID);
		node1->addGameObject(go.ID);


		ModuleInfo<GameObjekt> goMoon = gameRoot.hGameObject.create();
		ModuleInfo<ModuleTransformation> transformationMoon = gameRoot.hTransformation.create();
		ModuleInfo<ModuleTransformation> transformationMoonRot = gameRoot.hTransformation.create();
		ModuleInfo<ModuleTransformation> transformationMoonTrans = gameRoot.hTransformation.create();

		goMoon->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("sphere"));
		goMoon->addModule<ModuleTransformation>(transformationMoon.ID);
		goMoon->addModule<ModuleMaterial>(moonMaterial.ID);
		goMoon->setSceneID(scene.ID);

		ModuleInfo<SceneNode> moonTransNode = gameRoot.hSceneNode.create();
		ModuleInfo<SceneNode> moonRotNode = gameRoot.hSceneNode.create();

		transformationMoonTrans->translateY(10);

		node1->addChild(moonRotNode.ID);
		moonRotNode->addChild(moonTransNode.ID);

		moonTransNode->addGameObject(goMoon.ID);

		moonRotation = transformationMoonRot.ID;
		moonOwnRotation = transformationMoon.ID;
		//rootNode->addChild(node.ID);
	}

	{
		//Setup Portal
		ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
		ModuleInfo<ModuleTransformation> transformation = gameRoot.hTransformation.create();
		ModuleInfo<ModulePortal> portal = gameRoot.hPortal.create();

		go->addModule<ModuleTransformation>(transformation.ID);
		go->addModule<ModulePortal>(portal.ID);
		go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("plane"));
		go->setSceneID(scene.ID);

		rootNode->addGameObject(go.ID);

		portal->setStartGameObject(go.ID);

		transformation->scaleAbsolute(10, 10, 1);
		transformation->translateAbsolute(20, 30, -50);
		portalEnd = portal.ID;
	}

	//{  //Green Plane
	//	ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
	//	ModuleInfo<ModuleTransformation> transformation = gameRoot.hTransformation.create();

	//	transformation->scaleAbsolute(500.0f, 0.01f, 500.0f);

	//	go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("cube"));
	//	go->addModule<ModuleTransformation>(transformation.ID);
	//	go->addModule<ModuleMaterial>(gameRoot.hMaterial.getID("green"));
	//	go->setSceneID(scene.ID);

	//	rootNode->addGameObject(go.ID);
	//}

	//{ //Orange Portal Wall
	//	ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
	//	ModuleInfo<ModuleTransformation> transformation = gameRoot.hTransformation.create();

	//	transformation->scaleAbsolute(20, 20, 1.0f);
	//	transformation->translateAbsolute(10, 10, 0);

	//	go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("cube"));
	//	go->addModule<ModuleTransformation>(transformation.ID);
	//	go->addModule<ModuleMaterial>(gameRoot.hMaterial.getID("orange"));
	//	go->setSceneID(scene.ID);

	//	rootNode->addGameObject(go.ID);
	//}

	//{ //Blue Portal Wall
	//	ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
	//	ModuleInfo<ModuleTransformation> transformation = gameRoot.hTransformation.create();

	//	transformation->scaleAbsolute(20, 20, 1.0f);
	//	transformation->translateAbsolute(50, 10, 0);

	//	go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("cube"));
	//	go->addModule<ModuleTransformation>(transformation.ID);
	//	go->addModule<ModuleMaterial>(gameRoot.hMaterial.getID("blue"));
	//	go->setSceneID(scene.ID);

	//	rootNode->addGameObject(go.ID);
	//}

	//{ //Red Ape
	//	ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
	//	ModuleInfo<ModuleTransformation> transformation = gameRoot.hTransformation.create();

	//	transformation->scaleAbsolute(5, 5, 5);
	//	transformation->translateAbsolute(10, 10, 30);

	//	go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("ape"));
	//	go->addModule<ModuleTransformation>(transformation.ID);
	//	go->addModule<ModuleMaterial>(gameRoot.hMaterial.getID("red"));
	//	go->setSceneID(scene.ID);

	//	rootNode->addGameObject(go.ID);
	//}
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
	//ModuleTransformation* transformation = gameRoot.hTransformation.get(sunRotation);
	//transformation->rotateY(0.000005);

	//transformation = gameRoot.hTransformation.get(earthRotation);
	//transformation->rotateY(0.000005);
	//
	//transformation = gameRoot.hTransformation.get(earthOwnRotation);
	//transformation->rotateY(0.000005);

	//transformation = gameRoot.hTransformation.get(moonRotation);
	//transformation->rotateY(0.000005);

	//transformation = gameRoot.hTransformation.get(moonOwnRotation);
	//transformation->rotateY(0.000005);
}
