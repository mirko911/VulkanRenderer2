#include "CommandPool.hpp"

void CommandPool::Init(const VkDevice& device, const Queue& queueGraphics)
{
	m_device = device;
	m_queueGraphics = queueGraphics;
}

void CommandPool::create()
{
	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	poolInfo.queueFamilyIndex = m_queueGraphics.getIndex();

	if (vkCreateCommandPool(m_device, &poolInfo, nullptr, &m_commandPool) != VK_SUCCESS) {
		ABORT_F("Failed to create commandpool");
	}
}

CommandBuffer CommandPool::allocateCommandBuffer()
{
	CommandBuffer commandBuffer;
	commandBuffer.Init(m_device);
	commandBuffer.create(m_commandPool);
	return commandBuffer;
}

VkCommandPool& CommandPool::getCommandPool()
{
	return m_commandPool;
}
