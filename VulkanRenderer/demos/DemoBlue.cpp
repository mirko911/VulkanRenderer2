#include "DemoBlue.hpp"

void DemoBlue::initBlueWorld(GameRoot& gameRoot)
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

	{ //Red Ape
		ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
		ModuleInfo<ModuleTransformation> transformation = gameRoot.hTransformation.create();

		transformation->scaleAbsolute(5, 5, 5);
		transformation->translateAbsolute(50, 10, 30);

		go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("ape"));
		go->addModule<ModuleTransformation>(transformation.ID);
		go->addModule<ModuleMaterial>(gameRoot.hMaterial.getID("blue"));
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
		//Setup Portal #1
		ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
		ModuleInfo<ModuleTransformation> transformation = gameRoot.hTransformation.create();
		ModuleInfo<ModulePortal> portal = gameRoot.hPortal.create();

		go->addModule<ModuleTransformation>(transformation.ID);
		go->addModule<ModulePortal>(portal.ID);
		go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("plane"));
		go->setSceneID(scene.ID);

		portal->setStartGameObject(go.ID);
		portal->setSameScenePortal(true);

		rootNode->addGameObject(go.ID);
		scene->m_portals.push_back(portal.ID);

		transformation->scaleAbsolute(10, 10, 1);
		transformation->translateAbsolute(10, 10, 1);
	}

	{
		//Setup Portal #2
		ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
		ModuleInfo<ModuleTransformation> transformation = gameRoot.hTransformation.create();
		ModuleInfo<ModulePortal> portal = gameRoot.hPortal.create();

		go->addModule<ModuleTransformation>(transformation.ID);
		go->addModule<ModulePortal>(portal.ID);
		go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("plane"));
		go->setSceneID(scene.ID);

		portal->setStartGameObject(go.ID);
		portal->setSameScenePortal(true);

		rootNode->addGameObject(go.ID);
		scene->m_portals.push_back(portal.ID);

		transformation->scaleAbsolute(10, 10, 1);
		transformation->translateAbsolute(50, 10, 1);
	}

	int32_t sceneCloneID = scene->clone(gameRoot);
	int32_t sceneCloneID2 = scene->clone(gameRoot);

	Scene* sceneClone = gameRoot.hScene.get(sceneCloneID);
	Scene* sceneClone2 = gameRoot.hScene.get(sceneCloneID2);

	{
		ModulePortal* s0p0 = gameRoot.hPortal.get(scene->m_portals[0]);
		ModulePortal* s0p1 = gameRoot.hPortal.get(scene->m_portals[1]);

		ModulePortal* s1p1 = gameRoot.hPortal.get(sceneClone->m_portals[1]);
		ModulePortal* s2p0 = gameRoot.hPortal.get(sceneClone2->m_portals[0]);

		s0p0->setDestinatioNGameObject(s1p1->getStartGameObject());
		s0p1->setDestinatioNGameObject(s2p0->getStartGameObject());
	}

	scenes.push_back(sceneCloneID);
	scenes.push_back(sceneCloneID2);
}

void DemoBlue::init(GameRoot& gameRoot)
{
	initBlueWorld(gameRoot);
}


void DemoBlue::run(GameRoot& gameRoot)
{
	gameRoot.m_mainScene = mainScene;
	gameRoot.m_activeScenes = scenes;

	EventDrawCall drawCallEvent = EventDrawCall(gameRoot);
	HandlerEvent::instance().notify("redraw", drawCallEvent);
}

void DemoBlue::update(const float fTimeDelta, GameRoot& gameRoot)
{

}
