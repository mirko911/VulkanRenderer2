#include "HandlerCamera.hpp"

std::unordered_map<int32_t, std::unique_ptr<Camera>>& HandlerCamera::getAll()
{
	return m_entities;
}
