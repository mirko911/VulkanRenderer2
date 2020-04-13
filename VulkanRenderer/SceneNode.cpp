#include "SceneNode.hpp"

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

void SceneNode::update(const float fTimeDelta)
{
}
