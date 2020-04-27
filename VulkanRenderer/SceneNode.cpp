#include "SceneNode.hpp"
#include "GameRoot.hpp"

void SceneNode::setModuleID(const int32_t ID)
{
	m_moduleID = ID;
}

int32_t SceneNode::getModuleID() const
{
	return m_moduleID;
}


void SceneNode::setDebugName(const std::string& name)
{
	m_debugName = name;
}

std::string SceneNode::getDebugName() const
{
	return m_debugName;
}

void SceneNode::setTransformationID(const int32_t ID)
{
	m_transformationID = ID;
}

void SceneNode::addGameObject(const int32_t ID)
{
	m_gameObjects.push_back(ID);
}

void SceneNode::addChild(const int32_t ID)
{
	m_childs.push_back(ID);
}

std::vector<int32_t>& SceneNode::getChilds()
{
	return m_childs;
}

std::vector<int32_t>& SceneNode::getGameObjects()
{
	return m_gameObjects;
}

int32_t SceneNode::getTransformationID()
{
	return m_transformationID;
}


void SceneNode::update(const float fTimeDelta, GameRoot& gameRoot)
{
	//ModuleTransformation* transformationParent = gameRoot.hTransformation.get(m_transformationID);
	
}

void SceneNode::traverse2(GameRoot& gameRoot, SceneNode* parentNode, Mat4& globalMat)
{
	std::vector<int32_t>& gameObjects = parentNode->getGameObjects();
	if (!gameObjects.empty()) {
		for (const int32_t gameObjectID : gameObjects) {
			GameObject* gameobject = gameRoot.hGameObject.get(gameObjectID);
			ModuleTransformation* transform = gameRoot.hTransformation.get(gameobject);
			transform->updateGlobalMat(globalMat);
		}
	}

	for (const int32_t childID : parentNode->getChilds()) {
		SceneNode* childNode = gameRoot.hSceneNode.get(childID);
		
		Mat4 newMat(1.0f);
		if (childNode->getTransformationID() != ENTITY_NOT_FOUND) {
			ModuleTransformation* childTransform = gameRoot.hTransformation.get(childNode->getTransformationID());
			newMat = childTransform->updateGlobalMat(globalMat);
		}

		traverse2(gameRoot, childNode, newMat);
	}
}
