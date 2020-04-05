#include "HandlerGeometry.hpp"

HandlerGeometry::HandlerGeometry()
{
	setDebugName("HandlerGeometry");
}

std::unordered_map<int32_t, std::unique_ptr<ModuleGeometry>>& HandlerGeometry::getAll()
{
	return m_entities;
}