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

void SceneNode::setGameobjectID(const int32_t ID)
{
	m_gameObjectID = ID;
}

void SceneNode::addChild(const int32_t ID)
{
	m_childs.push_back(ID);
}

std::vector<int32_t>& SceneNode::getChilds()
{
	return m_childs;
}

int32_t SceneNode::getTransformationID()
{
	return m_transformationID;
}

int32_t SceneNode::getGameObjectID()
{
	return m_gameObjectID;
}

void SceneNode::update(const float fTimeDelta, GameRoot& gameRoot)
{
	//ModuleTransformation* transformationParent = gameRoot.hTransformation.get(m_transformationID);
	
}

void SceneNode::traverse(GameRoot& gameRoot, const int32_t ID, Mat4& globalMat)
{
	SceneNode* parentNode = gameRoot.hSceneNode.get(ID);
	ModuleTransformation* parentTransform = gameRoot.hTransformation.get(parentNode->getTransformationID());

	if (parentNode->getGameObjectID() != ENTITY_NOT_FOUND) {
		GameObjekt* gameobject = gameRoot.hGameObject.get(parentNode->getGameObjectID());
		ModuleTransformation* transform = gameRoot.hTransformation.get(gameobject);
		transform->updateGlobalMat(globalMat);
	}

	for (const int32_t childID : parentNode->getChilds()) {
		SceneNode* childNode = gameRoot.hSceneNode.get(childID);
		ModuleTransformation* childTransform = gameRoot.hTransformation.get(childNode->getTransformationID());

		Mat4 newMat = childTransform->updateGlobalMat(globalMat);
		traverse(gameRoot, childID, newMat);
	}

}

void SceneNode::traverse2(GameRoot& gameRoot, SceneNode* parentNode, Mat4& globalMat)
{

	ModuleTransformation* parentTransform = gameRoot.hTransformation.get(parentNode->getTransformationID());

	if (parentNode->getGameObjectID() != ENTITY_NOT_FOUND) {
		GameObjekt* gameobject = gameRoot.hGameObject.get(parentNode->getGameObjectID());
		ModuleTransformation* transform = gameRoot.hTransformation.get(gameobject);
		transform->updateGlobalMat(globalMat);
	}

	for (const int32_t childID : parentNode->getChilds()) {
		SceneNode* childNode = gameRoot.hSceneNode.get(childID);
		ModuleTransformation* childTransform = gameRoot.hTransformation.get(childNode->getTransformationID());

		Mat4 newMat = childTransform->updateGlobalMat(globalMat);
		traverse2(gameRoot, childNode, newMat);
	}
}
