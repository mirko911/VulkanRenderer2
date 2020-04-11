#include "HandlerSkybox.hpp"

std::unordered_map<int32_t, std::unique_ptr<Skybox>>& HandlerSkybox::getAll()
{
	return m_entities;
}
