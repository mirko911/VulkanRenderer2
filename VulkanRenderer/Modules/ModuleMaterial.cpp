#include "ModuleMaterial.hpp"

//void ModuleMaterial::update(const float ftimeDelta, GameRoot& gameRoot)
//{
//}

void ModuleMaterial::init(VulkanDevice& device)
{
}

void ModuleMaterial::setAmbientColor(const Vec4 color)
{
	m_material.ambientColor = color;
}

void ModuleMaterial::setDiffuseColor(const Vec4 color)
{
	m_material.diffuseColor = color;
}

void ModuleMaterial::setSpecularColor(const Vec4 color)
{
	m_material.specularColor = color;
}

void ModuleMaterial::setTextureID(const uint32_t ID)
{
	m_material.textureID = ID;
}

void ModuleMaterial::setNormalMapID(const uint32_t ID)
{
	m_material.normalMapID = ID;
}

void ModuleMaterial::setAmbientStrength(const float strength)
{
	m_material.strength.x = strength;
}

void ModuleMaterial::setSpecularStrength(const float strength)
{
	m_material.strength.y = strength;
}

MaterialBlock& ModuleMaterial::getMaterialBlock()
{
	return m_material;
}
