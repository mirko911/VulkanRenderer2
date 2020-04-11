#include "Renderer.hpp"

void Renderer::Init(VulkanDevice& device, GameRoot& gameRoot)
{
	m_vulkanDevice = device;
	//===============================================================================
	//Init Gamelogik
	//===============================================================================
	gameRoot.hGeometry.init(device);
	gameRoot.hTexture.init(device);
	gameRoot.hInput.init(device);
	gameRoot.hTransformation.init(device);
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
	m_renderpass.addAttachment(VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, true);
	m_renderpass.addAttachment(VK_FORMAT_D32_SFLOAT_S8_UINT, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, false);
	m_renderpass.addSubpass(colorAttachRef, depthAttachRef);
	m_renderpass.createRenderpass();

	//===============================================================================
	//Init Buffers
	//===============================================================================
	const VkPhysicalDeviceProperties deviceProperties = device.getDeviceProperties();
	const VkDeviceSize uboAlignment = deviceProperties.limits.minUniformBufferOffsetAlignment;
	m_dynamicAlignment = (sizeof(MainUBODyn)) > uboAlignment ? static_cast<VkDeviceSize>(sizeof(MainUBODyn)) : uboAlignment;

	Buffer::createBuffer(device.getDevice(), device.getGPU(),
		VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		m_buffers.mainUBO,
		sizeof(MainUBO)
	);

	Buffer::createBuffer(device.getDevice(), device.getGPU(),
		VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		m_buffers.mainUBODyn,
		sizeof(MainUBODyn) * MAX_DYNUBO_SIZE
	);

	//===============================================================================
	//Fill UBO-Buffers
	//===============================================================================
	updateUniformBuffer(gameRoot);

	//===============================================================================
	//Init Descriptors
	//===============================================================================
	Descriptor descriptor;
	descriptor.Init(device.getDevice());
	descriptor.addLayoutBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, static_cast<uint32_t>(gameRoot.hTexture.getAll2D().size()));
	descriptor.addLayoutBinding(1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT);
	descriptor.addLayoutBinding(2, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, VK_SHADER_STAGE_VERTEX_BIT);

	descriptor.createDescriptorSetLayout();

	std::vector<Descriptor> descriptors = { descriptor };

	DescriptorPool descriptorPool;
	descriptorPool.Init(device.getDevice(), device.getGPU());
	descriptorPool.create(descriptors);
	descriptorPool.allocateDescriptorSets(descriptors);


	std::vector<VkDescriptorImageInfo> imageInfos;
	imageInfos.reserve(gameRoot.hTexture.getAll2D().size());
	for (auto& texture2D : gameRoot.hTexture.getAll2D()) {
		imageInfos.emplace_back(std::move(texture2D.second->getDescriptorImageInfo()));
	}

	descriptors[0].writeSet(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, imageInfos);
	descriptors[0].writeSet(1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, m_buffers.mainUBO);
	descriptors[0].writeSet(2, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, m_buffers.mainUBODyn);

	//===============================================================================
	//Init Pipeline
	//===============================================================================
	m_pipeline.Init(device.getDevice(), m_renderpass, m_shader);
	std::vector<VkDescriptorSetLayout> layoutInfo = { descriptors[0].getDescriptorSetLayout()};
	m_pipeline.getDepthStencil().depthTestEnable = VK_FALSE;
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
		m_renderpass.createFrameBuffer(views, 1280, 720, 1);
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

	//===============================================================================
	//Record command buffers (draw calls)
	//===============================================================================
	m_commandBuffers.reserve(m_swapchain.getImageCount());
	for (uint32_t i = 0; i < m_swapchain.getImageCount(); i++) {
		CommandBuffer commandbuffer = m_commandPool.allocateCommandBuffer();

		commandbuffer.beginCommandBuffer();
		auto beginInfo = m_renderpass.getBeginInfo(color, i);
		commandbuffer.beginRenderPass(beginInfo);

		commandbuffer.bindPipeline(m_pipeline);

		for (auto& gameobject : gameRoot.hGameObject.getAll()) {
			const uint32_t offset = static_cast<uint32_t>(gameobject.first) * static_cast<uint32_t>(m_dynamicAlignment);

			ModuleGeometry* geometry = gameRoot.hGeometry.get<ModuleGeometry>(gameobject.second.get());

			commandbuffer.bindDescriptorSets(m_pipeline.getPipelineLayout(), descriptors[0].getDescriptorSet(), &offset);
			commandbuffer.bindVertexBuffers(geometry->getVertexBuffer().buffer);
			commandbuffer.bindIndexBuffers(geometry->getIndexBuffer().buffer);
			commandbuffer.drawIndexed(static_cast<uint32_t>(geometry->getIndexData().size()));
		}
		


		

		commandbuffer.endRenderPass();
		commandbuffer.endCommandBuffer();

		m_commandBuffers.push_back(commandbuffer);

	}
}

void Renderer::Render(GameRoot& gameRoot)
{
	vkWaitForFences(m_vulkanDevice.getDevice(), 1, &m_inFlightFences[m_currentFrame], VK_TRUE, UINT64_MAX);
	m_swapchain.beginFrame(m_imageAvailableSemaphore[m_currentFrame]);
	if (m_imagesInFlight[m_swapchain.getImageIndex()] != VK_NULL_HANDLE) {
		vkWaitForFences(m_vulkanDevice.getDevice(), 1, &m_imagesInFlight[m_swapchain.getImageIndex()], VK_TRUE, UINT64_MAX);
	}
	
	updateUniformBuffer(gameRoot);

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

void Renderer::updateUniformBuffer(GameRoot& gameRoot)
{
	Scene* scene = gameRoot.hScene.get(0);
	Camera* camera = gameRoot.hCamera.get(scene->m_activeCamera);

	MainUBO ubo;
	ubo.proj = camera->getProjection();
	ubo.view = camera->getView();
	ubo.viewProj = ubo.proj * ubo.view;
	ubo.position = Vec4(camera->getPosition(), 1.0f);

	m_buffers.mainUBO.map();
	memcpy(m_buffers.mainUBO.mapped, &ubo, sizeof(MainUBO));
	m_buffers.mainUBO.unmap();

	MainUBODyn dynUBO;
	for (auto& gameObjectPair : gameRoot.hGameObject.getAll()) {
		ModuleTransformation* transform = gameRoot.hTransformation.get(gameObjectPair.second.get());

		dynUBO.modelMat = transform->getLocalMat();

		m_buffers.mainUBODyn.map();
		void* ptr = static_cast<char*>(m_buffers.mainUBODyn.mapped) + (gameObjectPair.first * m_dynamicAlignment);
		memcpy(ptr, &dynUBO, sizeof(MainUBODyn));
		m_buffers.mainUBODyn.unmap();
	}
}


void Renderer::Destroy()
{
	return;
	m_shader.Destroy();
	m_pipeline.Destroy();
	m_renderpass.Destroy();
	m_swapchain.Destroy();
}
