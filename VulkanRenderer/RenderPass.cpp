#include "RenderPass.hpp"

void RenderPass::Init(const VkDevice& device)
{
	m_device = device;
}

void RenderPass::Destroy()
{
	vkDestroyRenderPass(m_device, m_renderpass, nullptr);
}

void RenderPass::addAttachment(const VkFormat& format, const VkImageLayout imageLayout, bool clearAttachment)
{
	VkAttachmentDescription attachDescription = {};

	attachDescription.format = format;
	attachDescription.samples = VK_SAMPLE_COUNT_1_BIT;
	attachDescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	attachDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE;
	attachDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	attachDescription.finalLayout = imageLayout;

	if (clearAttachment) {
		attachDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		attachDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	}
	else {
		attachDescription.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	}

	m_attachments.push_back(attachDescription);
}

void RenderPass::addSubpass(const VkAttachmentReference& colorRef, const VkAttachmentReference& depthRef)
{
	VkSubpassDescription subpassDesc = {};

	subpassDesc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpassDesc.colorAttachmentCount = 1;
	subpassDesc.pColorAttachments = &colorRef;
	subpassDesc.pDepthStencilAttachment = &depthRef;

	m_subpasses.push_back(subpassDesc);
}

void RenderPass::addSubpassDepth(const VkAttachmentReference& depthRef)
{
	VkSubpassDescription subpassDesc = {};

	subpassDesc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpassDesc.pDepthStencilAttachment = &depthRef;

	m_subpasses.push_back(subpassDesc);
}

void RenderPass::addSubPassDependency(uint32_t src_subpass, uint32_t dstSubpass)
{
	//DependencyTemplate::Stencil_Subpass_Bottom
	VkSubpassDependency dependency = {};
	dependency.srcSubpass = src_subpass;
	dependency.dstSubpass = dstSubpass;
	dependency.srcStageMask = VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT;
	dependency.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
	dependency.dstStageMask = VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT;
	dependency.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT | VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;

	m_dependencys.push_back(dependency);
}

void RenderPass::createRenderpass()
{
	VkRenderPassCreateInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = static_cast<uint32_t>(m_attachments.size());
	renderPassInfo.pAttachments = m_attachments.data();
	renderPassInfo.subpassCount = static_cast<uint32_t>(m_subpasses.size());
	renderPassInfo.pSubpasses = m_subpasses.data();
	renderPassInfo.dependencyCount = static_cast<uint32_t>(m_dependencys.size());
	renderPassInfo.pDependencies = m_dependencys.data();

	if (vkCreateRenderPass(m_device, &renderPassInfo, nullptr, &m_renderpass) != VK_SUCCESS) {
		ABORT_F("Failed to create renderpass");
	}
}

void RenderPass::prepareFrameBuffer(const std::vector<VkImageView>& imageViews, uint32_t width, uint32_t height, uint32_t layerCount)
{
	m_imageWidth = width;
	m_imageHeight = height;

	VkFramebufferCreateInfo framebufferInfo = {};
	framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	framebufferInfo.renderPass = m_renderpass;
	framebufferInfo.attachmentCount = static_cast<uint32_t>(imageViews.size());
	framebufferInfo.pAttachments = imageViews.data();
	framebufferInfo.width = width;
	framebufferInfo.height = height;
	framebufferInfo.layers = layerCount;

	VkFramebuffer frameBuffer;
	if (vkCreateFramebuffer(m_device, &framebufferInfo, nullptr, &frameBuffer) != VK_SUCCESS) {
		ABORT_F("Failed to create framebuffer");
	}

	m_frameBuffers.emplace_back(std::move(frameBuffer));
}


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

VkRenderPassBeginInfo RenderPass::getBeginInfo(const VkClearColorValue& backgroundColor, const uint32_t index)
{
	m_clearValues.resize(m_attachments.size());
	for (uint32_t i = 0; i < m_attachments.size(); ++i) {
		if (m_attachments[i].finalLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL ||
			m_attachments[i].finalLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL) {
			m_clearValues[i].depthStencil = { 1.0f, 0 };
			//m_clearValues[i].depthStencil.stencil = 0.0f;
			//m_clearValues[i].depthStencil.depth = 1.0f;

		}
		else {
			m_clearValues[i].color = backgroundColor;
			//m_clearValues[i].depthStencil.stencil = 0.0f;
		}
	}

	VkRenderPassBeginInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = m_renderpass;
	renderPassInfo.framebuffer = m_frameBuffers[index];
	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = { m_imageWidth, m_imageHeight };
	renderPassInfo.clearValueCount = static_cast<uint32_t>(m_clearValues.size());
	renderPassInfo.pClearValues = m_clearValues.data();

	return renderPassInfo;
}
