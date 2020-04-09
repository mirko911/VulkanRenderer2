#include "ModuleGeometry.hpp"

void ModuleGeometry::update(const float ftimeDelta)
{
}

void ModuleGeometry::init(VulkanDevice& device)
{
	LOG_F(INFO, "Created geometry %s (V: %i, I: %i)", m_debugName.c_str(), m_vertex.size(), m_index.size());


	const VkDeviceSize vertexBufferSize = sizeof(Vertex) * m_vertex.size();
	const VkDeviceSize indexbufferSize = sizeof(uint32_t) * m_index.size();

	if (vertexBufferSize == 0 || indexbufferSize == 0) {
		ABORT_F("Vertex and/or indexbuffer size is 0");
	}

	Buffer vertexStaging, indexStaging;

	Buffer::createBuffer(device.getDevice(), device.getGPU(),
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		vertexStaging,
		vertexBufferSize,
		m_vertex.data()
	);

	Buffer::createBuffer(device.getDevice(), device.getGPU(),
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		indexStaging,
		indexbufferSize,
		m_index.data()
	);

	// Create device local target buffers
			// Vertex buffer
	Buffer::createBuffer(device.getDevice(), device.getGPU(),
		VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		m_bufferVertex,
		vertexBufferSize);

	// Index buffer
	Buffer::createBuffer(device.getDevice(), device.getGPU(),
		VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		m_bufferIndex,
		indexbufferSize);

	CommandBuffer copyCmdBuffer = device.getCommandPool().allocateCommandBuffer();

	copyCmdBuffer.beginCommandBuffer(true);

	VkBufferCopy copyRegion{};

	copyRegion.size = vertexBufferSize;
	copyCmdBuffer.copyBuffer(vertexStaging.buffer, m_bufferVertex.buffer, 1, &copyRegion);

	copyRegion.size = indexbufferSize;
	copyCmdBuffer.copyBuffer(indexStaging.buffer, m_bufferIndex.buffer, 1, &copyRegion);


	copyCmdBuffer.endCommandBuffer();

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &copyCmdBuffer.get();

	// Create fence to ensure that the command buffer has finished executing
	VkFenceCreateInfo fenceCreateInfo{};
	fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceCreateInfo.flags = 0;

	VkFence fence;
	vkCreateFence(device.getDevice(), &fenceCreateInfo, nullptr, &fence);

	// Submit to the queue
	vkQueueSubmit(device.getGraphicsQueue().getQueue(), 1, &submitInfo, fence);
	// Wait for the fence to signal that command buffer has finished executing
	vkWaitForFences(device.getDevice(), 1, &fence, VK_TRUE, 10000000);

	vkDestroyFence(device.getDevice(), fence, nullptr);

	//free = true;
	vkFreeCommandBuffers(device.getDevice(), device.getCommandPool().getCommandPool(), 1, &copyCmdBuffer.get());


	// Destroy staging resources
	vkDestroyBuffer(device.getDevice(), vertexStaging.buffer, nullptr);
	vkFreeMemory(device.getDevice(), vertexStaging.memory, nullptr);
	vkDestroyBuffer(device.getDevice(), indexStaging.buffer, nullptr);
	vkFreeMemory(device.getDevice(), indexStaging.memory, nullptr);
}

Buffer& ModuleGeometry::getVertexBuffer()
{
	return m_bufferVertex;
}

Buffer& ModuleGeometry::getIndexBuffer()
{
	return m_bufferIndex;
}
