#pragma once

#include <loguru.hpp>
#include <vulkan/vulkan.hpp>


#include "Queue.hpp"
#include "RenderPass.hpp"
#include "Pipeline.hpp"
class CommandBuffer
{
private:
	VkDevice m_device = VK_NULL_HANDLE;
	VkCommandBuffer m_commandBuffer = VK_NULL_HANDLE;
	VkRenderPass m_renderPass = VK_NULL_HANDLE;
	VkFramebuffer m_frameBuffer = VK_NULL_HANDLE;

public:
	void Init(const VkDevice& device);
	void create(const VkCommandPool& commandPool);
	void beginCommandBuffer(const bool oneTime = false);
	void beginRenderPass(VkRenderPassBeginInfo& beginInfo);
	void endRenderPass();
	void endCommandBuffer();
	void bindPipeline(Pipeline& pipeline);
	void bindVertexBuffers(VkBuffer* buffers, VkDeviceSize* offset);
	void bindVertexBuffers(VkBuffer& buffers);
	void bindIndexBuffers(VkBuffer buffer, VkDeviceSize offset);
	void bindIndexBuffers(VkBuffer& buffer);
	void drawIndexed(uint32_t indexCount);
	void drawQuad();
	void nextSubpass();
	void bindDescriptorSets(VkPipelineLayout& pipelineLayout, std::vector<VkDescriptorSet> descriptorSets, uint32_t dynOffset);
	void bindDescriptorSets(const VkPipelineLayout& pipelineLayout, const VkDescriptorSet& descriptorSet);
	void bindDescriptorSets(const VkPipelineLayout& pipelineLayout, const VkDescriptorSet& descriptorSet, const uint32_t* dynOffset );

	void setStencilWriteMask(const uint32_t writeMask, const VkStencilFaceFlags flags = VK_STENCIL_FACE_FRONT_AND_BACK);
	void setStencilCompareMask(const uint32_t compareMask, const VkStencilFaceFlags flags = VK_STENCIL_FACE_FRONT_AND_BACK);

	void copyBuffer(VkBuffer& fromBuffer, VkBuffer& toBuffer, const uint32_t regionCount = 0, const VkBufferCopy* regionp = nullptr);
	void copyBufferToImage(VkBuffer& fromBuffer, VkImage& toImage, const VkImageLayout layout, const uint32_t regionCount = 0, const VkBufferImageCopy* regionp = nullptr);
	VkCommandBuffer& get();
};

