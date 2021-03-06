#include "HandlerSceneNode.hpp"

std::unordered_map<int32_t, std::unique_ptr<SceneNode>>& HandlerSceneNode::getAll()
{
	return m_entities;
}

void HandlerSceneNode::update(const float fTimeDelta, GameRoot& gameRoot)
{
}

void HandlerSceneNode::clear()
{
	m_entities.clear();
	HandlerBase::clear();
}
