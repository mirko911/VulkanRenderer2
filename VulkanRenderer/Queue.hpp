#pragma once

#include <loguru.hpp>
#include <vulkan/vulkan.h>
class Queue
{
private:
	VkQueue m_queue;
	uint32_t m_index;
public:
	void Init(const VkDevice& device, const uint32_t index);
	VkQueue& getQueue();
	uint32_t getIndex() const;
};

