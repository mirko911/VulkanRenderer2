#include "ModulePortal.hpp"

//void ModulePortal::update(const float ftimeDelta, GameRoot& gameRoot)
//{
//}

void ModulePortal::init(VulkanDevice& device)
{
}

void ModulePortal::setStartGameObject(const int32_t ID)
{
	m_startGameobjectID = ID;
}

void ModulePortal::setDestinatioNGameObject(const int32_t ID)
{
	m_destinationGameobjectID = ID;
}

int32_t ModulePortal::getStartGameObject() const
{
	return m_startGameobjectID;
}

int32_t ModulePortal::getDestinationGameObject() const
{
	return m_destinationGameobjectID;
}
