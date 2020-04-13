#include "HandlerSceneNode.hpp"

std::unordered_map<int32_t, std::unique_ptr<SceneNode>>& HandlerSceneNode::getAll()
{
	return m_entities;
}
