#pragma once

#include <vector>

#include <loguru.hpp>
#include <vulkan/vulkan.hpp>

#include "defintions.hpp"
#include "Shader.hpp"
#include "RenderPass.hpp"

class Pipeline
{
protected:
	VkDevice m_device;
	VkPipeline m_pipeline;
	VkPipelineLayout m_pipelineLayout;
	RenderPass m_renderPass;
	Shader m_shader;

	std::vector<VkDynamicState> m_dynamicState;

	std::array<VkVertexInputBindingDescription, 1>  bindingDescription;
	std::array<VkVertexInputAttributeDescription, 6> attributeDescription;
	VkPipelineVertexInputStateCreateInfo m_vertexInputInfo = {};
	VkPipelineInputAssemblyStateCreateInfo m_inputAssembly = {};
	VkViewport m_viewport = {};
	VkRect2D m_scissor = {};
	VkPipelineViewportStateCreateInfo m_viewportState = {};
	VkPipelineRasterizationStateCreateInfo m_rasterizer = {};
	VkPipelineMultisampleStateCreateInfo m_multisampling = {};
	VkPipelineDepthStencilStateCreateInfo m_depthStencil = {};
	VkPipelineColorBlendAttachmentState m_colorBlendAttachment = {};
	VkPipelineColorBlendStateCreateInfo m_colorBlending = {};
	VkPipelineLayoutCreateInfo m_pipelineLayoutInfo = {};
	VkGraphicsPipelineCreateInfo m_pipelineInfo = {};
	VkPipelineDynamicStateCreateInfo m_dynamicStateInfo = {};

	virtual void fillPipelineStructs();
public:
	Pipeline();
	Pipeline(const Pipeline& pipeline);
	virtual VkPipelineVertexInputStateCreateInfo& getVertexInputInfo();
	virtual VkPipelineInputAssemblyStateCreateInfo& getInputAssemblyState();
	virtual VkViewport& getViewport();
	virtual VkRect2D& getScissor();
	virtual VkPipelineViewportStateCreateInfo& getViewportState();
	virtual VkPipelineRasterizationStateCreateInfo& getRasterizer();
	virtual VkPipelineMultisampleStateCreateInfo& getMultisampling();
	virtual VkPipelineDepthStencilStateCreateInfo& getDepthStencil();
	virtual VkPipelineColorBlendAttachmentState& getColorBlendAttachment();
	virtual VkPipelineColorBlendStateCreateInfo& getColorBlendState();
	virtual VkPipelineLayoutCreateInfo& getPipelineLayoutInfo();
	virtual VkGraphicsPipelineCreateInfo& getPipelineInfo();

	Shader& getShader();
	RenderPass& getRenderPass();
	VkPipeline& get();
	VkPipelineLayout& getPipelineLayout();

	void createLayoutInfo(std::vector<VkDescriptorSetLayout>& descriptorSetLayouts);
	void createPipeline(const uint32_t subpass);
	void Init(VkDevice& device, RenderPass& renderpass, Shader& shader);
	void Destroy();
	void setDebugName(const std::string& name);


};

