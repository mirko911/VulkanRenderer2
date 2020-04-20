#include "GameObjekt.hpp"
#include "GameRoot.hpp"

void GameObjekt::setModuleID(const int32_t ID)
{
	m_moduleID = ID;
}

int32_t GameObjekt::getModuleID() const
{
	return m_moduleID;
}

void GameObjekt::setSceneID(const int32_t ID)
{
	m_sceneID = ID;
}

int32_t GameObjekt::getSceneID() const
{
	return m_sceneID;
}

void GameObjekt::setDebugName(const std::string& name)
{
	m_debugName = name;
}

std::string GameObjekt::getDebugName() const
{
	return m_debugName;
}

std::unordered_map<std::type_index, int32_t> GameObjekt::getModules() const
{
	return m_modules;
}

void GameObjekt::setModules(const std::unordered_map<std::type_index, int32_t> modules)
{
	m_modules = modules;
}

void GameObjekt::addChild(const int32_t ID)
{
	m_children.push_back(ID);
}

std::vector<int32_t> GameObjekt::getChildren() const
{
	return m_children;
}

bool GameObjekt::hasChildren()
{
	return !m_children.empty();
}

void GameObjekt::removeChild(const int32_t ID)
{
	LOG_F(WARNING, "removeChild() is not implemented yet");
}

void GameObjekt::removeAllChildren(const int32_t ID)
{
	m_children.clear();
}

int32_t GameObjekt::clone(GameRoot& gameRoot)
{
	ModuleInfo<GameObjekt> gameobjectClone = gameRoot.hGameObject.create();

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
