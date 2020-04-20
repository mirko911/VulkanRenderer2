#include "Scene.hpp"

#include "GameRoot.hpp"
#include "SceneNode.hpp"

void Scene::setModuleID(const int32_t ID)
{
	m_moduleID = ID;
}

int32_t Scene::getModuleID() const
{
	return m_moduleID;
}

void Scene::addRootNode(const int32_t ID)
{
	m_rootNodes.push_back(ID);
}

std::vector<int32_t> Scene::getRootNodes()
{
	return m_rootNodes;
}

int32_t Scene::clone(GameRoot& gameRoot)
{
	ModuleInfo<Scene> sceneClone = gameRoot.hScene.create();

	for (const int32_t rootNode : getRootNodes()) {
		ModuleInfo<SceneNode> rootNodeClone = gameRoot.hSceneNode.create();
		sceneClone->addRootNode(rootNodeClone.ID);

		SceneNode* node = gameRoot.hSceneNode.get(rootNode);
		traverse(gameRoot, sceneClone.ID, node, rootNodeClone.instance);
	}

	ModuleInfo<Camera> cameraClone = gameRoot.hCamera.create();
	Camera* camera = gameRoot.hCamera.get(m_activeCamera);
	cameraClone->setPosition(camera->getPosition(), camera->getYaw(), camera->getPitch());
	cameraClone->setProjection(camera->getProjection());

	sceneClone->m_activeCamera = cameraClone.ID;
	sceneClone->m_skyboxID = m_skyboxID;

	return sceneClone.ID;
}

void Scene::traverse(GameRoot& gameRoot, const int32_t sceneID, SceneNode* parentNode, SceneNode* parentNodeClone)
{
	for (const int32_t gamebobjectID : parentNode->getGameObjects()) {
		GameObjekt* gameobject = gameRoot.hGameObject.get(gamebobjectID);
		int32_t goClone = gameobject->clone(gameRoot);
		GameObjekt* gameobjectClone = gameRoot.hGameObject.get(goClone);
		gameobjectClone->setSceneID(sceneID);

		if (gameobjectClone->hasModule<ModulePortal>()) {
			int32_t portalID = gameobjectClone->getModule<ModulePortal>();
			Scene* scene = gameRoot.hScene.get(sceneID);
			scene->m_portals.push_back(portalID);
		}

		parentNodeClone->addGameObject(goClone);
	}

	if (parentNode->getTransformationID() != ENTITY_NOT_FOUND) {
		ModuleInfo<ModuleTransformation> transformationClone = gameRoot.hTransformation.create();
		ModuleTransformation* transformation = gameRoot.hTransformation.get(parentNode->getTransformationID());

		transformationClone->setTransformation(transformation->getTransformation());
		parentNodeClone->setTransformationID(transformationClone.ID);
	}

	for (const int32_t childNode : parentNode->getChilds()) {
		SceneNode* node = gameRoot.hSceneNode.get(childNode);
		ModuleInfo<SceneNode> nodeClone = gameRoot.hSceneNode.create();
		parentNodeClone->addChild(nodeClone.ID);

		traverse(gameRoot, sceneID, node, nodeClone.instance);
	}
}

void Scene::setDebugName(const std::string& name)
{
	m_debugName = name;
}

std::string Scene::getDebugName() const
{
	return m_debugName;
}