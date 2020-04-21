#include "HandlerBase.hpp"

int32_t HandlerBase::getNextModuleID()
{
	int32_t id = 0;
	if (!m_freeIDs.empty()) {
		id = m_freeIDs.front();
		m_freeIDs.pop_front();
	}
	else {
		id = m_nextID++;
	}
	return id;
}


void HandlerBase::init(VulkanDevice& device)
{
}

void HandlerBase::update(const float fTimeDelta, GameRoot& gameRoot)
{
}

void HandlerBase::addAlias(const int32_t ID, const std::string& alias)
{
	m_aliases[alias] = ID;
}

void HandlerBase::removeAlias(const std::string& alias)
{
	m_aliases.erase(alias);
}

void HandlerBase::removeAliases(const int32_t ID)
{
	for (const auto& alias : m_aliases) {
		if (alias.second == ID) {
			m_aliases.erase(alias.first);
		}
	}
}

void HandlerBase::removeAliases()
{
	m_aliases.clear();
}

int32_t HandlerBase::getID(const std::string& alias)
{
	if (m_aliases.find(alias) != m_aliases.end()) {
		return m_aliases[alias];
	}

	return ENTITY_NOT_FOUND;
}

void HandlerBase::setDebugName(const std::string& name)
{
	m_debugName = name;
}

std::string HandlerBase::getDebugName() const
{
	return m_debugName;
}

void HandlerBase::clear()
{
	removeAliases();
	m_nextID = 0;
}
