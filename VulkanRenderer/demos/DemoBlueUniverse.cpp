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
	scene->m_skyboxID = gameRoot.hSkybox.getID("universe");
	sceneUniverse = scene.ID;
	//mainScene = scene.ID;


	ModuleInfo<ModuleTransformation> sunTransformation = gameRoot.hTransformation.create();
	ModuleInfo<ModuleTransformation> earthTransformation = gameRoot.hTransformation.create();
	ModuleInfo<ModuleTransformation> moonTransformation = gameRoot.hTransformation.create();


	ModuleInfo<SceneNode> earthNode1 = gameRoot.hSceneNode.create();
	ModuleInfo<SceneNode> earthNode2 = gameRoot.hSceneNode.create();
	ModuleInfo<SceneNode> moonNode1 = gameRoot.hSceneNode.create();
	ModuleInfo<SceneNode> moonNode2 = gameRoot.hSceneNode.create();

	ModuleInfo<ModuleTransformation> earthNodeTransform1 = gameRoot.hTransformation.create(); //orbital rotation
	ModuleInfo<ModuleTransformation> earthNodeTransform2 = gameRoot.hTransformation.create(); //orbital rotation
	ModuleInfo<ModuleTransformation> moonNodeTransform1 = gameRoot.hTransformation.create(); //orbital rotation
	ModuleInfo<ModuleTransformation> moonNodeTransform2 = gameRoot.hTransformation.create(); //orbital rotation

	{
		ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();

		go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("sphere"));
		go->addModule<ModuleTransformation>(sunTransformation.ID);
		go->addModule<ModuleMaterial>(gameRoot.hMaterial.getID("sun"));
		go->setSceneID(scene.ID);
		rootNode->addGameObject(go.ID);
	}
	{
		ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();

		go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("sphere"));
		go->addModule<ModuleTransformation>(earthTransformation.ID);
		go->addModule<ModuleMaterial>(gameRoot.hMaterial.getID("earth"));
		go->setSceneID(scene.ID);
		earthNode2->addGameObject(go.ID);
	}
	{
		ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();

		go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("sphere"));
		go->addModule<ModuleTransformation>(moonTransformation.ID);
		go->addModule<ModuleMaterial>(gameRoot.hMaterial.getID("moon"));
		go->setSceneID(scene.ID);
		moonNode2->addGameObject(go.ID);
	}

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


	sunTransformation->scaleAbsolute(Vec3(20.0f));
	earthTransformation->scaleAbsolute(Vec3(10.0f));
	moonTransformation->scaleAbsolute(Vec3(1.0f));

	rootNode->addChild(earthNode1.ID);
	earthNode1->addChild(earthNode2.ID);

	earthNode2->addChild(moonNode1.ID);
	moonNode1->addChild(moonNode2.ID);

	earthNode1->setTransformationID(earthNodeTransform1.ID);
	earthNode2->setTransformationID(earthNodeTransform2.ID);
	moonNode1->setTransformationID(moonNodeTransform1.ID);
	moonNode2->setTransformationID(moonNodeTransform2.ID);

	m_sunTransformation = sunTransformation.ID;
	m_earthTransformation = earthTransformation.ID;
	m_moonTransformation = moonTransformation.ID;

	m_earthNode1Transformation = earthNodeTransform1.ID;
	m_moonNode1Transformation = moonNodeTransform1.ID;

	earthNodeTransform2->translateAbsoluteX(85.0f);
	moonNodeTransform2->translateAbsoluteX(20.0f);

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
	
	EventDrawCall drawCallEvent = EventDrawCall(gameRoot);
	HandlerEvent::instance().notify("redraw", drawCallEvent);
}

void DemoBlueUniverse::update(const float fTimeDelta, GameRoot& gameRoot)
{
	ModuleTransformation* transformation = gameRoot.hTransformation.get(m_sunTransformation);
	transformation->rotateY(0.00005);

	transformation = gameRoot.hTransformation.get(m_earthTransformation);
	transformation->rotateY(0.0005);
	
	transformation = gameRoot.hTransformation.get(m_moonTransformation);
	transformation->rotateY(0.005);

	transformation = gameRoot.hTransformation.get(m_earthNode1Transformation);
	transformation->rotateY(0.0005);

	transformation = gameRoot.hTransformation.get(m_moonNode1Transformation);
	transformation->rotateY(0.0005);
}
