#include "HandlerScene.hpp"

std::unordered_map<int32_t, std::unique_ptr<Scene>>& HandlerScene::getAll()
{
	return m_entities;
}

void HandlerScene::clear()
{
	m_entities.clear();
	HandlerBase::clear();
}
