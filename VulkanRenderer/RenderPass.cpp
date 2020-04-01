#include "RenderPass.hpp"

VkRenderPass& RenderPass::get()
{
	return m_renderpass;
}

VkExtent2D RenderPass::getExtend()
{
	return { 1280, 720 };
}

uint32_t RenderPass::getWidth()
{
	return 1280;
}

uint32_t RenderPass::getHeight()
{
	return 720;
}
