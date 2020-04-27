#include "HandlerMaterial.hpp"

std::unordered_map<int32_t, std::unique_ptr<ModuleMaterial>>& HandlerMaterial::getAll()
{
	return m_entities;
}

void HandlerMaterial::init(VulkanDevice& device)
{
	for (auto& ent : m_entities) {
		ent.second->init(device);
	}
}
