#pragma once
#include <string>

#include "defintions.hpp"

class Scene
{
private:
	int32_t m_moduleID = ENTITY_NOT_FOUND;
	std::string m_debugName = "Generic Gameobject";
public:
	void setDebugName(const std::string& name);
	std::string getDebugName() const;

	void setModuleID(const int32_t ID);
	int32_t getModuleID() const;

	int32_t m_activeCamera = ENTITY_NOT_FOUND;
};

