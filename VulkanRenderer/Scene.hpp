#pragma once
#include <string>

#include "defintions.hpp"

class GameRoot;
class SceneNode;

class Scene
{
private:
	int32_t m_moduleID = ENTITY_NOT_FOUND;
	std::string m_debugName = "Generic Gameobject";
	std::vector<int32_t> m_rootNodes;

	void traverse(GameRoot& gameRoot, const int32_t sceneID, SceneNode* parentNode, SceneNode* parentNodeClone);

public:
	void setDebugName(const std::string& name);
	std::string getDebugName() const;

	void setModuleID(const int32_t ID);
	int32_t getModuleID() const;

	void addRootNode(const int32_t ID);
	std::vector<int32_t> getRootNodes();

	int32_t clone(GameRoot& gameRoot);

	int32_t m_activeCamera = ENTITY_NOT_FOUND;
	int32_t m_skyboxID = ENTITY_NOT_FOUND;
	uint32_t stencilColor = 0x0;

	std::vector<int32_t> m_portals;
};

