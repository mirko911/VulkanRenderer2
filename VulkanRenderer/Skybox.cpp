#include "Skybox.hpp"

void Skybox::setModuleID(const int32_t ID)
{
	m_moduleID = ID;
}

int32_t Skybox::getModuleID() const
{
	return m_moduleID;
}

Skybox::Skybox(const int32_t textureID, const int geoID) : m_textureID(textureID), m_geoID(geoID)
{
}

int32_t Skybox::getTextureID() const
{
	return m_textureID;
}

int32_t Skybox::getGeoID() const
{
	return m_geoID;
}

void Skybox::setDebugName(const std::string& name)
{
	m_debugName = name;
}

std::string Skybox::getDebugName() const
{
	return m_debugName;
}