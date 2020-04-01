#pragma once
#include <loguru.hpp>
#include <vulkan/vulkan.hpp>

#include "CommandBuffer.hpp"
#include "Queue.hpp"
class CommandPool
{
private:
	VkDevice m_device = VK_NULL_HANDLE;
	Queue m_queueGraphics;
	VkCommandPool m_commandPool = VK_NULL_HANDLE;

public:
	void Init(const VkDevice& device, const Queue& queueGraphics);
	void create();
	CommandBuffer allocateCommandBuffer();
	VkCommandPool& getCommandPool();
};

