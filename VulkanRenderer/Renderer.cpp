#include "Renderer.hpp"

void Renderer::Init(VulkanDevice& device)
{
	m_vulkanDevice = device;

	//===============================================================================
	//Init Shader
	//===============================================================================
	m_shader.Init(device.getDevice());
	m_shader.addShaderStage(VK_SHADER_STAGE_VERTEX_BIT, "shaders/main.vert.spv");
	m_shader.addShaderStage(VK_SHADER_STAGE_FRAGMENT_BIT, "shaders/main.frag.spv");

	//===============================================================================
	//Init Renderpass
	//===============================================================================
	VkAttachmentReference colorAttachRef = {};
	colorAttachRef.attachment = 0;
	colorAttachRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkAttachmentReference depthAttachRef = {};
	depthAttachRef.attachment = 1;
	depthAttachRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	m_renderpass.Init(device.getDevice());
	m_renderpass.addAttachment(VK_FORMAT_B8G8R8A8_UNORM, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, false);
	m_renderpass.addAttachment(VK_FORMAT_D32_SFLOAT_S8_UINT, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, false);
	m_renderpass.addSubpass(colorAttachRef, depthAttachRef);
	m_renderpass.createRenderpass();

	//===============================================================================
	//Init Pipeline
	//===============================================================================
	m_pipeline.Init(device.getDevice(), m_renderpass, m_shader);
	std::vector<VkDescriptorSetLayout> layoutInfo;
	m_pipeline.createLayoutInfo(layoutInfo);
	m_pipeline.createPipeline(0);

	//===============================================================================
	//Init Swapchain
	//===============================================================================
	m_swapchain.Init(device.getDevice(), device.getGPU(), device.getSurface(), device.getGraphicsQueue(), device.getPresentQueue(), 1280, 720);
	m_swapchain.create();
	m_swapchain.createImageViews();
}

void Renderer::Destroy()
{
	m_shader.Destroy();
	m_pipeline.Destroy();
	m_renderpass.Destroy();
	m_swapchain.Destroy();
}
