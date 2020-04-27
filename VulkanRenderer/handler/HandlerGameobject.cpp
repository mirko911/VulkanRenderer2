#include "HandlerGameobject.hpp"

std::unordered_map<int32_t, std::unique_ptr<GameObject>>& HandlerGameobject::getAll()
{
	return m_entities;
}

void HandlerGameobject::clear()
{
	m_entities.clear();
	HandlerBase::clear();
}
