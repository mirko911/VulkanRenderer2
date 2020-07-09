#include "PipelineFont.hpp"

void PipelineFont::fillPipelineStructs()
{
	Pipeline::fillPipelineStructs();

	m_colorBlendAttachment = {};
	m_colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	m_colorBlendAttachment.blendEnable = VK_TRUE;
	m_colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
	m_colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
	m_colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
	m_colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	m_colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	m_colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;

	m_colorBlending.pAttachments = &m_colorBlendAttachment;

	m_rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	m_rasterizer.lineWidth = 1.0f;
	m_rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	m_rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;


	vertexInputBindings[0] = { 0, sizeof(glm::vec4), VK_VERTEX_INPUT_RATE_VERTEX };
	vertexInputBindings[1] = { 1, sizeof(glm::vec4), VK_VERTEX_INPUT_RATE_VERTEX };
	vertexInputAttributes[0] = { 0, 0, VK_FORMAT_R32G32_SFLOAT, 0 };					//Location 0: Position
	vertexInputAttributes[1] = { 1, 1, VK_FORMAT_R32G32_SFLOAT, sizeof(glm::vec2) };   //Location 1: UV

	m_vertexInputInfo = {};
	m_vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	m_vertexInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(vertexInputBindings.size());
	m_vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexInputAttributes.size());
	m_vertexInputInfo.pVertexBindingDescriptions = vertexInputBindings.data();
	m_vertexInputInfo.pVertexAttributeDescriptions = vertexInputAttributes.data();

	m_inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
}


void PipelineFont::createPipeline(const uint32_t subpass)
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
	pipelineInfo.pColorBlendState = &m_colorBlending;
	pipelineInfo.layout = m_pipelineLayout;
	pipelineInfo.renderPass = m_renderPass.get();
	pipelineInfo.subpass = subpass;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
	pipelineInfo.basePipelineIndex = 0;
	pipelineInfo.pDynamicState = (!m_dynamicState.empty()) ? &m_dynamicStateInfo : nullptr;

	if (vkCreateGraphicsPipelines(m_device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_pipeline) != VK_SUCCESS) {
		ABORT_F("Failed to create graphics pipeline");
	}
}
