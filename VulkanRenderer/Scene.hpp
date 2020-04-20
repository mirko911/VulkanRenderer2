#pragma once
#include <string>

#include "defintions.hpp"

class Scene
{
private:
	int32_t m_moduleID = ENTITY_NOT_FOUND;
	std::string m_debugName = "Generic Gameobject";
	std::vector<int32_t> m_rootNodes;
public:
	void setDebugName(const std::string& name);
	std::string getDebugName() const;

	void setModuleID(const int32_t ID);
	int32_t getModuleID() const;

	void addRootNode(const int32_t ID);
	std::vector<int32_t> getRootNodes();

	int32_t m_activeCamera = ENTITY_NOT_FOUND;
	int32_t m_skyboxID = ENTITY_NOT_FOUND;
	uint32_t stencilColor = 0x0;
};

