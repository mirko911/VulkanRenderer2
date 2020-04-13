#include "ModuleBase.hpp"

void ModuleBase::init(VulkanDevice& device)
{
}

void ModuleBase::update(const float ftimeDelta, GameRoot& gameRoot)
{
}

void ModuleBase::setModuleID(const uint32_t moduleID)
{
	m_moduleID = moduleID;
}

uint32_t ModuleBase::getModuleID() const
{
	return m_moduleID;
}
