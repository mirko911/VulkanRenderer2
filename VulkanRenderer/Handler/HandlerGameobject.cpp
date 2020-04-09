#include "HandlerGameobject.hpp"

std::unordered_map<int32_t, std::unique_ptr<GameObjekt>>& HandlerGameobject::getAll()
{
	return m_entities;
}
