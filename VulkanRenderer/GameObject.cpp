#include "GameObject.hpp"
#include "GameRoot.hpp"

void GameObject::setModuleID(const int32_t ID)
{
	m_moduleID = ID;
}

int32_t GameObject::getModuleID() const
{
	return m_moduleID;
}

void GameObject::setSceneID(const int32_t ID)
{
	m_sceneID = ID;
}

int32_t GameObject::getSceneID() const
{
	return m_sceneID;
}

void GameObject::setDebugName(const std::string& name)
{
	m_debugName = name;
}

std::string GameObject::getDebugName() const
{
	return m_debugName;
}

std::unordered_map<std::type_index, int32_t> GameObject::getModules() const
{
	return m_modules;
}

void GameObject::setModules(const std::unordered_map<std::type_index, int32_t> modules)
{
	m_modules = modules;
}

void GameObject::addChild(const int32_t ID)
{
	m_children.push_back(ID);
}

std::vector<int32_t> GameObject::getChildren() const
{
	return m_children;
}

bool GameObject::hasChildren()
{
	return !m_children.empty();
}

void GameObject::removeChild(const int32_t ID)
{
	LOG_F(WARNING, "removeChild() is not implemented yet");
}

void GameObject::removeAllChildren(const int32_t ID)
{
	m_children.clear();
}

int32_t GameObject::clone(GameRoot& gameRoot)
{
	ModuleInfo<GameObject> gameobjectClone = gameRoot.hGameObject.create();

	//Copy all modules
	gameobjectClone->setModules(m_modules);

	if (hasModule<ModulePortal>()) {
		ModuleInfo<ModulePortal> portalClone = gameRoot.hPortal.create();
		portalClone->setStartGameObject(gameobjectClone.ID);
		//Overwrite old portal with new one
		gameobjectClone->addModule<ModulePortal>(portalClone.ID, true);
	}

	if (hasModule<ModuleTransformation>()) {
		ModuleTransformation* transformation = gameRoot.hTransformation.get(this);
		ModuleInfo<ModuleTransformation> transformationClone = gameRoot.hTransformation.create();
		transformationClone->setTransformation(transformation->getTransformation());
		gameobjectClone->addModule<ModuleTransformation>(transformationClone.ID, true);
	}

	return gameobjectClone.ID;
}
