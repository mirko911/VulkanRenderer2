#pragma once
#include <string>

#include "defintions.hpp"

class Skybox
{
private:
	int32_t m_moduleID = ENTITY_NOT_FOUND;
	std::string m_debugName = "Generic Skybox";
	
	int32_t m_textureID;
	int32_t m_geoID;
public:
	void setDebugName(const std::string& name);
	std::string getDebugName() const;

	void setModuleID(const int32_t ID);
	int32_t getModuleID() const;

	int32_t m_activeCamera = ENTITY_NOT_FOUND;

	Skybox(const int32_t textureID, const int geoID);

	int32_t getTextureID() const;
	int32_t getGeoID() const;
};

