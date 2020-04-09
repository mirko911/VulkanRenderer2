#include "HandlerTransformation.hpp"

std::unordered_map<int32_t, std::unique_ptr<ModuleTransformation>>& HandlerTransformation::getAll()
{
	return m_entities;
}
