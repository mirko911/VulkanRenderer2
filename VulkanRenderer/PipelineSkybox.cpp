#include "PipelineSkybox.hpp"

void PipelineSkybox::fillPipelineStructs()
{
	Pipeline::fillPipelineStructs();

	m_rasterizer = {};
	m_rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	m_rasterizer.depthClampEnable = VK_FALSE;
	m_rasterizer.rasterizerDiscardEnable = VK_FALSE;
	m_rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	m_rasterizer.lineWidth = 1.0f;
	m_rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	m_rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	m_rasterizer.depthBiasEnable = VK_FALSE;

	m_depthStencil = {};
	m_depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	m_depthStencil.pNext = NULL;
	m_depthStencil.flags = 0;
	m_depthStencil.depthTestEnable = VK_TRUE;
	m_depthStencil.depthWriteEnable = VK_FALSE;
	m_depthStencil.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
	m_depthStencil.depthBoundsTestEnable = VK_FALSE;
	m_depthStencil.minDepthBounds = 0;
	m_depthStencil.maxDepthBounds = 0;

	m_depthStencil.stencilTestEnable = VK_TRUE;
	m_depthStencil.back.failOp = VK_STENCIL_OP_KEEP;
	m_depthStencil.back.depthFailOp = VK_STENCIL_OP_KEEP;
	m_depthStencil.back.passOp = VK_STENCIL_OP_KEEP;
	m_depthStencil.back.compareOp = VK_COMPARE_OP_EQUAL;
	m_depthStencil.back.compareMask = 0xff;
	m_depthStencil.back.writeMask = 0xff;
	m_depthStencil.back.reference = 0xff;
	m_depthStencil.front = m_depthStencil.back;
}
