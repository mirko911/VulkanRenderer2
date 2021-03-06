#include "CommandBuffer.hpp"

void CommandBuffer::Init(const VkDevice& device)
{
	m_device = device;
}

void CommandBuffer::create(const VkCommandPool& commandPool)
{
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = commandPool;
	allocInfo.commandBufferCount = 1;

	if (vkAllocateCommandBuffers(m_device, &allocInfo, &m_commandBuffer) != VK_SUCCESS) {
		ABORT_F("Failed to allocate commandbuffer from commandpool");
	};
}

void CommandBuffer::beginCommandBuffer(const bool oneTime)
{
	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

	if (oneTime) {
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	}

	if (vkBeginCommandBuffer(m_commandBuffer, &beginInfo) != VK_SUCCESS) {
		ABORT_F("Failed to execute beginCommandBuffer");
	};
}

void CommandBuffer::beginRenderPass(VkRenderPassBeginInfo& beginInfo)
{
	m_renderPass = beginInfo.renderPass;
	m_frameBuffer = beginInfo.framebuffer;


	VkViewport viewport = {};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.x = (float)beginInfo.renderArea.offset.x;
	viewport.y = (float)beginInfo.renderArea.offset.y;
	viewport.width = (float)beginInfo.renderArea.extent.width;
	viewport.height = (float)beginInfo.renderArea.extent.height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	VkRect2D scissor = {};
	scissor.offset = { beginInfo.renderArea.offset.x, beginInfo.renderArea.offset.y };
	scissor.extent = beginInfo.renderArea.extent;

	vkCmdBeginRenderPass(m_commandBuffer, &beginInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void CommandBuffer::endRenderPass()
{
	vkCmdEndRenderPass(m_commandBuffer);
}

void CommandBuffer::endCommandBuffer()
{
	if (vkEndCommandBuffer(m_commandBuffer) != VK_SUCCESS) {
		ABORT_F("Failed to execute endcommandBuffer");
	};
}

void CommandBuffer::bindPipeline(Pipeline& pipeline)
{
	VkPipelineBindPoint bindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

	vkCmdBindPipeline(m_commandBuffer, bindPoint, pipeline.get());
}

void CommandBuffer::bindVertexBuffers(VkBuffer* buffers, VkDeviceSize* offset) {
	vkCmdBindVertexBuffers(m_commandBuffer, 0, 1, buffers, offset);
}

void CommandBuffer::bindVertexBuffers(VkBuffer& buffers)
{
	const VkDeviceSize null = 0;
	vkCmdBindVertexBuffers(m_commandBuffer, 0, 1, &buffers, &null);
}

void CommandBuffer::bindIndexBuffers(VkBuffer buffer, const VkDeviceSize offset) {
	vkCmdBindIndexBuffer(m_commandBuffer, buffer, offset, VK_INDEX_TYPE_UINT32);
}

void CommandBuffer::bindIndexBuffers(VkBuffer& buffer)
{
	vkCmdBindIndexBuffer(m_commandBuffer, buffer, 0, VK_INDEX_TYPE_UINT32);
}

void CommandBuffer::drawIndexed(const uint32_t indexCount) {
	vkCmdDrawIndexed(m_commandBuffer, indexCount, 1, 0, 0, 0);
}

void CommandBuffer::drawQuad() {
	vkCmdDraw(m_commandBuffer, 4, 1, 0, 0);
}

void CommandBuffer::nextSubpass() {
	vkCmdNextSubpass(m_commandBuffer, VK_SUBPASS_CONTENTS_INLINE);
}

void CommandBuffer::bindDescriptorSets(VkPipelineLayout& pipelineLayout, std::vector<VkDescriptorSet> descriptorSets, uint32_t dynOffset) {
	//vkCmdBindDescriptorSets(m_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, descriptorSets, 0, nullptr); //Vorher
	vkCmdBindDescriptorSets(m_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, 
		pipelineLayout, 0, static_cast<uint32_t>(descriptorSets.size()), descriptorSets.data()
		, 1, &dynOffset); //Nacher
}

void CommandBuffer::bindDescriptorSets(const VkPipelineLayout& pipelineLayout, const VkDescriptorSet& descriptorSet) {
	//vkCmdBindDescriptorSets(m_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, descriptorSets, 0, nullptr); //Vorher
	vkCmdBindDescriptorSets(m_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
		pipelineLayout, 0, static_cast<uint32_t>(1), &descriptorSet
		, 0, nullptr); //Nacher
}

void CommandBuffer::bindDescriptorSets(const VkPipelineLayout& pipelineLayout, const VkDescriptorSet& descriptorSet, const uint32_t* dynOffset)
{
	//vkCmdBindDescriptorSets(m_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, descriptorSets, 0, nullptr); //Vorher
	vkCmdBindDescriptorSets(m_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
		pipelineLayout, 0, static_cast<uint32_t>(1), &descriptorSet, 1, dynOffset); //Nacher
}

void CommandBuffer::setStencilWriteMask(const uint32_t writeMask, const VkStencilFaceFlags flags)
{
	vkCmdSetStencilWriteMask(m_commandBuffer, flags, writeMask);
}

void CommandBuffer::setStencilCompareMask(const uint32_t compareMask, const VkStencilFaceFlags flags)
{
	vkCmdSetStencilCompareMask(m_commandBuffer, flags, compareMask);
}

void CommandBuffer::copyBuffer(VkBuffer& fromBuffer, VkBuffer& toBuffer, const uint32_t regionCount , const VkBufferCopy* regionp )
{
	vkCmdCopyBuffer(m_commandBuffer, fromBuffer, toBuffer, regionCount, regionp);
}

void CommandBuffer::copyBufferToImage(VkBuffer& fromBuffer, VkImage& toImage, const VkImageLayout layout, const uint32_t regionCount, const VkBufferImageCopy* regionp)
{
	// Copy the cube map faces from the staging buffer to the optimal tiled image
	vkCmdCopyBufferToImage(
		m_commandBuffer,
		fromBuffer,
		toImage,
		layout,
		regionCount,
		regionp
	);
}

VkCommandBuffer& CommandBuffer::get() {
	return m_commandBuffer;
}
