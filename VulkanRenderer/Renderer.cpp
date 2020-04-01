#include "Renderer.hpp"

void Renderer::Init(VulkanDevice& device)
{
	m_vulkanDevice = device;

	//===============================================================================
	//Init Swapchain
	//===============================================================================
	m_swapchain.Init(device.getDevice(), device.getGPU(), device.getSurface(), device.getGraphicsQueue(), device.getPresentQueue(), 1280, 720);
	m_swapchain.create();
	m_swapchain.createImageViews();


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
	m_renderpass.addAttachment(VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, false);
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
	//Init FrameBuffers
	//===============================================================================
	Texture depthTexture;
	depthTexture.Init(device.getDevice(), device.getGPU(), device.getGraphicsQueue());
	depthTexture.createEmptyDepthImage(VK_FORMAT_D32_SFLOAT_S8_UINT, 1280, 720, 1, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, 1);

	for (uint32_t i = 0; i < m_swapchain.getImageCount(); i++) {
		std::vector<VkImageView> views{ m_swapchain.getImageViews()[i].get(), depthTexture.getImageView().get() };
		m_renderpass.prepareFrameBuffer(views, 1280, 720, 1);
	}

	//===============================================================================
	//Init Sync Objects
	//===============================================================================
	m_imageAvailableSemaphore.resize(MAX_FRAMES_IN_FLIGHT);
	m_renderFinishedSemaphore.resize(MAX_FRAMES_IN_FLIGHT);
	m_inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
	m_imagesInFlight.resize(MAX_FRAMES_IN_FLIGHT);

	VkSemaphoreCreateInfo semaphoreInfo = {};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkFenceCreateInfo fenceInfo = {};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		if (vkCreateSemaphore(device.getDevice(), &semaphoreInfo, nullptr, &m_imageAvailableSemaphore[i]) != VK_SUCCESS ||
			vkCreateSemaphore(device.getDevice(), &semaphoreInfo, nullptr, &m_renderFinishedSemaphore[i]) != VK_SUCCESS ||
			vkCreateFence(device.getDevice(), &fenceInfo, nullptr, &m_inFlightFences[i]) != VK_SUCCESS) {
			ABORT_F("Failed to create syncronization objections for frame %i", i);
		}
	}

	//===============================================================================
	//Init CommandBuffers
	//===============================================================================
	m_commandPool.Init(device.getDevice(), device.getGraphicsQueue());
	m_commandPool.create();

	const VkClearColorValue color = { 0.f,0.4831f, 0.78125f, 1.0f };


	m_commandBuffers.reserve(m_swapchain.getImageCount());
	for (uint32_t i = 0; i < m_swapchain.getImageCount(); i++) {
		CommandBuffer commandbuffer = m_commandPool.allocateCommandBuffer();
		m_commandBuffers.push_back(commandbuffer);

		commandbuffer.beginCommandBuffer();

		auto beginInfo = m_renderpass.getBeginInfo(color, i);
		commandbuffer.beginRenderPass(beginInfo);
		commandbuffer.bindPipeline(m_pipeline);
		commandbuffer.drawQuad();
		commandbuffer.endRenderPass();
		commandbuffer.endCommandBuffer();
	}
}

void Renderer::Render()
{
	vkWaitForFences(m_vulkanDevice.getDevice(), 1, &m_inFlightFences[m_currentFrame], VK_TRUE, UINT64_MAX);
	m_swapchain.beginFrame(m_imageAvailableSemaphore[m_currentFrame]);
	if (m_imagesInFlight[m_swapchain.getImageIndex()] != VK_NULL_HANDLE) {
		vkWaitForFences(m_vulkanDevice.getDevice(), 1, &m_imagesInFlight[m_swapchain.getImageIndex()], VK_TRUE, UINT64_MAX);
	}

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { m_imageAvailableSemaphore[m_currentFrame] };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &m_commandBuffers[m_swapchain.getImageIndex()].get();

	VkSemaphore signalSemaphores[] = { m_renderFinishedSemaphore[m_currentFrame] };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	vkResetFences(m_vulkanDevice.getDevice(), 1, &m_inFlightFences[m_currentFrame]);

	if (vkQueueSubmit(m_vulkanDevice.getGraphicsQueue().getQueue(), 1, &submitInfo, m_inFlightFences[m_currentFrame]) != VK_SUCCESS) {
		ABORT_F("Failed to submit draw command buffer");
	}

	m_swapchain.submitFrame(*signalSemaphores);
	m_currentFrame = (m_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

}


void Renderer::Destroy()
{
	m_shader.Destroy();
	m_pipeline.Destroy();
	m_renderpass.Destroy();
	m_swapchain.Destroy();
}
