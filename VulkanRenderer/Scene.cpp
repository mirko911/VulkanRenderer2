#include "Scene.hpp"
void Scene::setModuleID(const int32_t ID)
{
	m_moduleID = ID;
}

int32_t Scene::getModuleID() const
{
	return m_moduleID;
}

void Scene::setDebugName(const std::string& name)
{
	m_debugName = name;
}

std::string Scene::getDebugName() const
{
	return m_debugName;
}