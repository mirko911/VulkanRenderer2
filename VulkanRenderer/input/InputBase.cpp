#include "InputBase.hpp"

void InputBase::setModuleID(const int32_t ID)
{
	m_moduleID = ID;
}

int32_t InputBase::getModuleID() const
{
	return m_moduleID;
}

void InputBase::setDebugName(const std::string& name)
{
	m_debugName = name;
}

std::string InputBase::getDebugName() const
{
	return m_debugName;
}
