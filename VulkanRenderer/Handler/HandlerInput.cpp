#include "HandlerInput.hpp"


std::unordered_map<int32_t, std::unique_ptr<InputBase>>& HandlerInput::getAll()
{
	return m_entities;
}

void HandlerInput::init(VulkanDevice& device)
{
	for (auto& ent : m_entities) {
		ent.second->Init(device);
	}
}

void HandlerInput::update(const float fTimeDelta, GameRoot& gameRoot)
{
	for (auto& ent : m_entities) {
		ent.second->update(fTimeDelta);
	}
}
