#include "TextureCubemap.hpp"


void TextureCubemap::setModuleID(const int32_t ID)
{
	m_moduleID = ID;
}

int32_t TextureCubemap::getModuleID() const
{
	return m_moduleID;
}

void TextureCubemap::setDebugName(const std::string& name)
{
	m_debugName = name;
}

std::string TextureCubemap::getDebugName() const
{
	return m_debugName;
}