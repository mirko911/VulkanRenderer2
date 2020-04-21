#include "HandlerPortal.hpp"

std::unordered_map<int32_t, std::unique_ptr<ModulePortal>>& HandlerPortal::getAll()
{
	return m_entities;
}

void HandlerPortal::init(VulkanDevice& device)
{
	for (auto& ent : m_entities) {
		ent.second->init(device);
	}
}

void HandlerPortal::update(const float fTimeDelta, GameRoot& gameRoot)
{
	for (auto& ent : m_entities) {
		ent.second->update(fTimeDelta, gameRoot);
	}
}

void HandlerPortal::clear()
{
	m_entities.clear();
	HandlerBase::clear();
}
