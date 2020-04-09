#pragma once
#include <string>

#include "Texture.hpp"

class TextureCubemap : public Texture
{
private:
	int32_t m_moduleID = ENTITY_NOT_FOUND;
	std::string m_debugName = "Generic Cubemap";
public:
	void setModuleID(const int32_t ID);
	int32_t getModuleID() const;

	void setDebugName(const std::string& name);
	std::string getDebugName() const;
};

