#include "DemoMaterial.hpp"

void DemoMaterial::initBlueWorld(GameRoot& gameRoot)
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

	

	std::vector<int32_t> materials = {
		gameRoot.hMaterial.getID("default"), gameRoot.hMaterial.getID("orange"), gameRoot.hMaterial.getID("blue"), gameRoot.hMaterial.getID("green"), gameRoot.hMaterial.getID("red"),
		gameRoot.hMaterial.getID("christmas"), gameRoot.hMaterial.getID("fabric"), gameRoot.hMaterial.getID("rock"),gameRoot.hMaterial.getID("tile"),gameRoot.hMaterial.getID("plank"),
		gameRoot.hMaterial.getID("christmas-1"), gameRoot.hMaterial.getID("fabric-1"), gameRoot.hMaterial.getID("rock-1"),gameRoot.hMaterial.getID("tile-1"),gameRoot.hMaterial.getID("plank-1"),
		gameRoot.hMaterial.getID("christmas-2"), gameRoot.hMaterial.getID("fabric-2"), gameRoot.hMaterial.getID("rock-2"),gameRoot.hMaterial.getID("tile-2"),gameRoot.hMaterial.getID("plank-2"),
	};

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 5; x++) {
			ModuleInfo<GameObjekt> go = gameRoot.hGameObject.create();
			ModuleInfo<ModuleTransformation> transformation = gameRoot.hTransformation.create();

			transformation->scaleAbsolute(5, 5, 5);
			transformation->translateAbsolute(x * 20, 0, y * 20);

			m_transformations.push_back(transformation.ID);

			go->addModule<ModuleGeometry>(gameRoot.hGeometry.getID("ape"));
			go->addModule<ModuleTransformation>(transformation.ID);
			go->addModule<ModuleMaterial>(materials[(y * 5) + x]);
			go->setSceneID(scene.ID);

			rootNode->addGameObject(go.ID);
		}
	}

	scenes.push_back(scene.ID);
}

void DemoMaterial::init(GameRoot& gameRoot)
{
	initBlueWorld(gameRoot);
}


void DemoMaterial::run(GameRoot& gameRoot)
{
	gameRoot.m_mainScene = mainScene;
	gameRoot.m_activeScenes = scenes;

	EventDrawCall drawCallEvent = EventDrawCall(gameRoot);
	HandlerEvent::instance().notify("redraw", drawCallEvent);
}

void DemoMaterial::update(const float fTimeDelta, GameRoot& gameRoot)
{
	for (const int32_t transformationID : m_transformations) {
		ModuleTransformation* transformation = gameRoot.hTransformation.get(transformationID);
		transformation->rotateZ(0.0005f);
	}
}
