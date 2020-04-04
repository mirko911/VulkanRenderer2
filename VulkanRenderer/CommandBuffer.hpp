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
	void beginCommandBuffer();
	void beginRenderPass(VkRenderPassBeginInfo& beginInfo);
	void endRenderPass();
	void endCommandBuffer();
	void bindPipeline(Pipeline& pipeline);
	void bindVertexBuffers(VkBuffer* buffers, VkDeviceSize* offset);
	void bindIndexBuffers(VkBuffer buffer, VkDeviceSize offset);
	void drawIndexed(uint32_t indexCount);
	void drawQuad();
	void nextSubpass();
	void bindDescriptorSets(VkPipelineLayout& pipelineLayout, std::vector<VkDescriptorSet> descriptorSets, uint32_t dynOffset);
	void bindDescriptorSets(const VkPipelineLayout& pipelineLayout, const VkDescriptorSet& descriptorSet);
	VkCommandBuffer& get();
};

