#include "HandlerTransformation.hpp"

std::unordered_map<int32_t, std::unique_ptr<ModuleTransformation>>& HandlerTransformation::getAll()
{
	return m_entities;
}

void HandlerTransformation::init(VulkanDevice& device)
{
	for (auto& ent : m_entities) {
		ent.second->init(device);
	}
}

void HandlerTransformation::update(const float fTimeDelta, GameRoot& gameRoot)
{
	for (auto& ent : m_entities) {
		ent.second->update(fTimeDelta, gameRoot);
	}
}

void HandlerTransformation::clear()
{
	m_entities.clear();
	HandlerBase::clear();
}
