#include "PipelineDepth.hpp"

void PipelineDepth::createPipeline(const uint32_t subpass)
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
	pipelineInfo.pColorBlendState = nullptr;
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
