#include "Pipeline.hpp"

void Pipeline::fillPipelineStructs()
{
	//bindingDescription = Vertex::getBindingDescription();
	//attributeDescription = Vertex::getAttributeDescriptions();

	m_vertexInputInfo = {};
	m_vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	m_vertexInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(bindingDescription.size());
	m_vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescription.size());
	m_vertexInputInfo.pVertexBindingDescriptions = bindingDescription.data();
	m_vertexInputInfo.pVertexAttributeDescriptions = attributeDescription.data();

	m_inputAssembly = {};
	m_inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	m_inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	m_inputAssembly.primitiveRestartEnable = VK_FALSE;

	m_viewport = {};
	m_viewport.x = 0.0f;
	m_viewport.y = 0.0f;
	m_viewport.width = (float)m_renderPass.getWidth();
	m_viewport.height = (float)m_renderPass.getHeight();
	m_viewport.minDepth = 0.0f;
	m_viewport.maxDepth = 1.0f;

	m_scissor = {};
	m_scissor.offset = { 0, 0 };
	m_scissor.extent = { m_renderPass.getWidth(), m_renderPass.getHeight() };

	m_viewportState = {};
	m_viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	m_viewportState.viewportCount = 1;
	m_viewportState.pViewports = &m_viewport;
	m_viewportState.scissorCount = 1;
	m_viewportState.pScissors = &m_scissor;

	m_rasterizer = {};
	m_rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	m_rasterizer.depthClampEnable = VK_FALSE;
	m_rasterizer.rasterizerDiscardEnable = VK_FALSE;
	m_rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	m_rasterizer.lineWidth = 1.0f;
	m_rasterizer.cullMode = VK_CULL_MODE_FRONT_BIT;
	m_rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	m_rasterizer.depthBiasEnable = VK_FALSE;

	m_multisampling = {};
	m_multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	m_multisampling.sampleShadingEnable = VK_FALSE;
	m_multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	m_depthStencil = {};
	m_depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	m_depthStencil.pNext = NULL;
	m_depthStencil.flags = 0;
	m_depthStencil.depthTestEnable = VK_TRUE;
	m_depthStencil.depthWriteEnable = VK_TRUE;
	m_depthStencil.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
	m_depthStencil.depthBoundsTestEnable = VK_FALSE;
	m_depthStencil.minDepthBounds = 0;
	m_depthStencil.maxDepthBounds = 0;

	m_depthStencil.stencilTestEnable = VK_TRUE;
	m_depthStencil.back.failOp = VK_STENCIL_OP_REPLACE;
	m_depthStencil.back.depthFailOp = VK_STENCIL_OP_REPLACE;
	m_depthStencil.back.passOp = VK_STENCIL_OP_REPLACE;
	m_depthStencil.back.compareOp = VK_COMPARE_OP_ALWAYS;
	m_depthStencil.back.compareMask = 0xff;
	m_depthStencil.back.writeMask = 0xff;
	m_depthStencil.back.reference = 0x44;
	m_depthStencil.front = m_depthStencil.back;

	m_colorBlendAttachment = {};
	m_colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	m_colorBlendAttachment.blendEnable = VK_FALSE;
	m_colorBlendAttachment.blendEnable = VK_FALSE;
	m_colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
	m_colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
	m_colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ZERO;
	m_colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
	m_colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	m_colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;

	m_colorBlending = {};
	m_colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	m_colorBlending.logicOpEnable = VK_FALSE;
	m_colorBlending.logicOp = VK_LOGIC_OP_NO_OP;
	m_colorBlending.attachmentCount = 1;
	m_colorBlending.pAttachments = &m_colorBlendAttachment;
	m_colorBlending.blendConstants[0] = 1.0f;
	m_colorBlending.blendConstants[1] = 1.0f;
	m_colorBlending.blendConstants[2] = 1.0f;
	m_colorBlending.blendConstants[3] = 1.0f;
}

Pipeline::Pipeline()
{
}

Pipeline::Pipeline(const Pipeline& pipeline)
{
}

VkPipelineVertexInputStateCreateInfo& Pipeline::getVertexInputInfo()
{
	return m_vertexInputInfo;
}

VkPipelineInputAssemblyStateCreateInfo& Pipeline::getInputAssemblyState()
{
	return m_inputAssembly;
}

VkViewport& Pipeline::getViewport()
{
	return m_viewport;
}

VkRect2D& Pipeline::getScissor()
{
	return m_scissor;
}

VkPipelineViewportStateCreateInfo& Pipeline::getViewportState()
{
	return m_viewportState;
}

VkPipelineRasterizationStateCreateInfo& Pipeline::getRasterizer()
{
	return m_rasterizer;
}

VkPipelineMultisampleStateCreateInfo& Pipeline::getMultisampling()
{
	return m_multisampling;
}

VkPipelineDepthStencilStateCreateInfo& Pipeline::getDepthStencil()
{
	return m_depthStencil;
}

VkPipelineColorBlendAttachmentState& Pipeline::getColorBlendAttachment()
{
	return m_colorBlendAttachment;
}

VkPipelineColorBlendStateCreateInfo& Pipeline::getColorBlendState()
{
	return m_colorBlending;
}

VkPipelineLayoutCreateInfo& Pipeline::getPipelineLayoutInfo()
{
	return m_pipelineLayoutInfo;
}

VkGraphicsPipelineCreateInfo& Pipeline::getPipelineInfo()
{
	return m_pipelineInfo;
}

Shader& Pipeline::getShader()
{
	return m_shader;
}

RenderPass& Pipeline::getRenderPass()
{
	return m_renderPass;
}

VkPipeline& Pipeline::get()
{
	return m_pipeline;
}

VkPipelineLayout Pipeline::getPipelineLayout()
{
	return m_pipelineLayout;
}

void Pipeline::createLayoutInfo(std::vector<VkDescriptorSetLayout>& descriptorSetLayouts)
{
	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.pushConstantRangeCount = 0;
	pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
	pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());

	if (vkCreatePipelineLayout(m_device, &pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS) {
		ABORT_F("Failed to create pipeline layout");
	}
}

void Pipeline::createPipeline(const uint32_t subpass)
{
	m_dynamicStateInfo = {};
	m_dynamicStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	m_dynamicStateInfo.pDynamicStates = m_dynamicState.data();
	m_dynamicStateInfo.dynamicStateCount = static_cast<uint32_t>(m_dynamicState.size());

	VkGraphicsPipelineCreateInfo pipelineInfo = {};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = static_cast<uint32_t>(m_shader.getShaderStages().size());
	pipelineInfo.pStages = m_shader.getShaderStages().data();
	pipelineInfo.pVertexInputState = &m_vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &m_inputAssembly;
	pipelineInfo.pViewportState = &m_viewportState;
	pipelineInfo.pRasterizationState = &m_rasterizer;
	pipelineInfo.pMultisampleState = &m_multisampling;
	pipelineInfo.pDepthStencilState = &m_depthStencil;
	//pipelineInfo.pColorBlendState = (!depthOnly) ? &m_colorBlending : nullptr;
	pipelineInfo.pColorBlendState =  &m_colorBlending;
	pipelineInfo.layout = m_pipelineLayout;
	pipelineInfo.renderPass = m_renderPass.get();
	pipelineInfo.subpass = subpass;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
	pipelineInfo.basePipelineIndex = 0;
	//pipelineInfo.pDynamicState = (depthOnly || m_dynamic) ? &m_dynamicStateInfo : nullptr;
	pipelineInfo.pDynamicState =  nullptr;

	if (vkCreateGraphicsPipelines(m_device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_pipeline) != VK_SUCCESS) {
		ABORT_F("Failed to create graphics pipeline");
	}
}

void Pipeline::init(VkDevice& device, RenderPass& renderpass, Shader& shader)
{
	m_device = device;
	m_renderPass = renderpass;
	m_shader = shader;

	fillPipelineStructs();
}

void Pipeline::setDebugName(const std::string& name)
{
	//DebugMarker::setObjectName(
	//	m_device, 
	//	reinterpret_cast<uint64_t>(m_pipeline), 
	//	VK_DEBUG_REPORT_OBJECT_TYPE_SHADER_MODULE_EXT, 
	//	name.c_str()
	//);
}
