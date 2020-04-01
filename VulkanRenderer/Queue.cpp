#include "Queue.hpp"

void Queue::Init(const VkDevice& device, const uint32_t index)
{
	m_index = index;
	vkGetDeviceQueue(device, index, 0, &m_queue);
}

VkQueue& Queue::getQueue()
{
	return m_queue;
}

uint32_t Queue::getIndex() const
{
	return m_index;
}
