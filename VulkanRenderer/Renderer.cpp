#include "Renderer.hpp"

void Renderer::Init(VulkanDevice& device, GameRoot& gameRoot)
{
	m_vulkanDevice = device;

	//===============================================================================
	//Init Swapchain
	//===============================================================================
	uint32_t frameBufferWidth = 0;
	uint32_t frameBufferHeight = 0;
	device.getWindow().getFrameBufferSize(frameBufferWidth, frameBufferHeight);
	m_swapchain.Init(device.getDevice(), device.getGPU(), device.getSurface(), device.getGraphicsQueue(), device.getPresentQueue(), frameBufferWidth, frameBufferHeight);
	m_swapchain.create();
	m_swapchain.createImageViews();


	//===============================================================================
	//Init Shader
	//===============================================================================
	m_shaders.main.Init(device.getDevice());
	m_shaders.main.addShaderStage(VK_SHADER_STAGE_VERTEX_BIT, "shaders/main.vert.spv");
	m_shaders.main.addShaderStage(VK_SHADER_STAGE_FRAGMENT_BIT, "shaders/main.frag.spv");

	m_shaders.skybox.Init(device.getDevice());
	m_shaders.skybox.addShaderStage(VK_SHADER_STAGE_VERTEX_BIT, "shaders/skybox.vert.spv");
	m_shaders.skybox.addShaderStage(VK_SHADER_STAGE_FRAGMENT_BIT, "shaders/skybox.frag.spv");

	m_shaders.depth.Init(device.getDevice());
	m_shaders.depth.addShaderStage(VK_SHADER_STAGE_VERTEX_BIT, "shaders/depth.vert.spv");
	m_shaders.depth.addShaderStage(VK_SHADER_STAGE_FRAGMENT_BIT, "shaders/depth.frag.spv");

	//===============================================================================
	//Init Renderpass
	//===============================================================================
	VkAttachmentReference colorAttachRef = {};
	colorAttachRef.attachment = 0;
	colorAttachRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkAttachmentReference depthAttachRef = {};
	depthAttachRef.attachment = 1;
	depthAttachRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkFormat optimalDepthFormat = device.findDepthFormat();

	m_renderpass.Init(device.getDevice());
	m_renderpass.addAttachment(VK_FORMAT_B8G8R8A8_UNORM, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, true);
	m_renderpass.addAttachment(optimalDepthFormat, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, true);
	m_renderpass.addSubpassDepth(depthAttachRef); //Main Depth
	m_renderpass.addSubpassDepth(depthAttachRef); //Portal Depth
	m_renderpass.addSubpass(colorAttachRef, depthAttachRef);
	m_renderpass.addSubPassDependency(0, 1);
	m_renderpass.addSubPassDependency(1, 2);
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

	Buffer::createBuffer(device.getDevice(), device.getGPU(),
		VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		m_buffers.skyboxUBODyn,
		sizeof(SkyboxUBODyn) * 2
	);

	Buffer::createBuffer(device.getDevice(), device.getGPU(),
		VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		m_buffers.materialUBO,
		sizeof(MaterialUBO)
	);

	//===============================================================================
	//Fill UBO-Buffers
	//===============================================================================
	updateUniformBuffer(gameRoot, true);

	//===============================================================================
	//Init Descriptors
	//===============================================================================
	Descriptor descriptor;
	descriptor.Init(device.getDevice());
	descriptor.addLayoutBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, static_cast<uint32_t>(gameRoot.hTexture.getAll2D().size()));
	descriptor.addLayoutBinding(1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_FRAGMENT_BIT);
	descriptor.addLayoutBinding(2, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT);
	descriptor.addLayoutBinding(3, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, VK_SHADER_STAGE_VERTEX_BIT);
	descriptor.createDescriptorSetLayout();

	Descriptor descriptorSky;
	descriptorSky.Init(device.getDevice());
	descriptorSky.addLayoutBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, static_cast<uint32_t>(gameRoot.hTexture.getAllCubemap().size()));
	descriptorSky.addLayoutBinding(1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, VK_SHADER_STAGE_VERTEX_BIT);
	descriptorSky.createDescriptorSetLayout();

	std::vector<Descriptor> descriptors = { descriptor, descriptorSky };

	DescriptorPool descriptorPool;
	descriptorPool.Init(device.getDevice(), device.getGPU());
	descriptorPool.create(descriptors);
	descriptorPool.allocateDescriptorSets(descriptors);


	std::vector<VkDescriptorImageInfo> imageInfosMain;
	imageInfosMain.reserve(gameRoot.hTexture.getAll2D().size());
	for (auto& texture2D : gameRoot.hTexture.getAll2D()) {
		imageInfosMain.emplace_back(std::move(texture2D.second->getDescriptorImageInfo()));
	}

	std::vector<VkDescriptorImageInfo> imageInfosSky;
	imageInfosSky.reserve(gameRoot.hTexture.getAllCubemap().size());
	for (auto& textureCubemap : gameRoot.hTexture.getAllCubemap()) {
		imageInfosSky.emplace_back(std::move(textureCubemap.second->getDescriptorImageInfo()));
	}

	descriptors[0].writeSet(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, imageInfosMain);
	descriptors[0].writeSet(1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, m_buffers.materialUBO);
	descriptors[0].writeSet(2, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, m_buffers.mainUBO);
	descriptors[0].writeSet(3, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, m_buffers.mainUBODyn);

	descriptors[1].writeSet(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, imageInfosSky);
	descriptors[1].writeSet(1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, m_buffers.skyboxUBODyn);

	//===============================================================================
	//Init FrameBuffers
	//===============================================================================
	Texture depthTexture;
	depthTexture.Init(device.getDevice(), device.getGPU(), device.getGraphicsQueue());
	depthTexture.createEmptyDepthImage(optimalDepthFormat, frameBufferWidth, frameBufferHeight, 1, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, 1);

	for (uint32_t i = 0; i < m_swapchain.getImageCount(); i++) {
		std::vector<VkImageView> views{ m_swapchain.getImageViews()[i].get(), depthTexture.getImageView().get() };
		m_renderpass.createFrameBuffer(views, frameBufferWidth, frameBufferHeight, 1);
	}

	//===============================================================================
	//Init Pipeline
	//===============================================================================
	std::vector<VkDescriptorSetLayout> layoutInfoMain = { descriptors[0].getDescriptorSetLayout() };

	m_pipelines.mainDepth.Init(device.getDevice(), m_renderpass, m_shaders.depth);
	m_pipelines.mainDepth.addDynamicState(VK_DYNAMIC_STATE_STENCIL_WRITE_MASK);
	m_pipelines.mainDepth.addDynamicState(VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK);
	m_pipelines.mainDepth.getDepthStencil().depthTestEnable = VK_TRUE;
	m_pipelines.mainDepth.getDepthStencil().depthWriteEnable = VK_TRUE;
	m_pipelines.mainDepth.getDepthStencil().depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
	m_pipelines.mainDepth.createLayoutInfo(layoutInfoMain);
	m_pipelines.mainDepth.createPipeline(0);

	m_pipelines.portalDepth.Init(device.getDevice(), m_renderpass, m_shaders.depth);
	m_pipelines.portalDepth.addDynamicState(VK_DYNAMIC_STATE_STENCIL_WRITE_MASK);
	m_pipelines.portalDepth.addDynamicState(VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK);
	m_pipelines.portalDepth.getDepthStencil().depthTestEnable = VK_TRUE;
	m_pipelines.portalDepth.getDepthStencil().depthWriteEnable = VK_TRUE;
	m_pipelines.portalDepth.getDepthStencil().depthCompareOp = VK_COMPARE_OP_LESS;
	m_pipelines.portalDepth.getDepthStencil().back.compareOp = VK_COMPARE_OP_EQUAL;
	m_pipelines.portalDepth.getDepthStencil().back.failOp = VK_STENCIL_OP_KEEP;
	m_pipelines.portalDepth.getDepthStencil().back.depthFailOp = VK_STENCIL_OP_KEEP;
	m_pipelines.portalDepth.getDepthStencil().back.passOp = VK_STENCIL_OP_KEEP;
	m_pipelines.portalDepth.getDepthStencil().front = m_pipelines.portalDepth.getDepthStencil().back;
	m_pipelines.portalDepth.createLayoutInfo(layoutInfoMain);
	m_pipelines.portalDepth.createPipeline(1);


	m_pipelines.skybox.Init(device.getDevice(), m_renderpass, m_shaders.skybox);
	std::vector<VkDescriptorSetLayout> layoutInfoSky = { descriptors[1].getDescriptorSetLayout() };
	m_pipelines.skybox.createLayoutInfo(layoutInfoSky);
	m_pipelines.skybox.createPipeline(2);

	m_pipelines.main.Init(device.getDevice(), m_renderpass, m_shaders.main);
	m_pipelines.main.getDepthStencil().stencilTestEnable = VK_TRUE;
	m_pipelines.main.getDepthStencil().back.compareMask = 0x00;
	m_pipelines.main.getDepthStencil().back.compareOp = VK_COMPARE_OP_EQUAL;
	m_pipelines.main.getDepthStencil().front = m_pipelines.main.getDepthStencil().back;
	//m_pipelines.main.getDepthStencil().depthTestEnable = VK_FALSE;
	m_pipelines.main.createLayoutInfo(layoutInfoMain);
	m_pipelines.main.createPipeline(2);

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

		{
			//======================
			// Draw Main Scene Depth
			//======================
			commandbuffer.bindPipeline(m_pipelines.mainDepth);
			commandbuffer.setStencilWriteMask(0x00);
			commandbuffer.setStencilCompareMask(0xff);

			//Draw all objects of the main scene
			for (auto& gameobject : gameRoot.hGameObject.getAll()) {
				const uint32_t offset = static_cast<uint32_t>(gameobject.first)* static_cast<uint32_t>(m_dynamicAlignment);

				ModuleGeometry* geometry = gameRoot.hGeometry.get<ModuleGeometry>(gameobject.second.get());

				commandbuffer.bindDescriptorSets(m_pipelines.mainDepth.getPipelineLayout(), descriptors[0].getDescriptorSet(), &offset);
				commandbuffer.bindVertexBuffers(geometry->getVertexBuffer().buffer);
				commandbuffer.bindIndexBuffers(geometry->getIndexBuffer().buffer);
				commandbuffer.drawIndexed(static_cast<uint32_t>(geometry->getIndexData().size()));
			}

			commandbuffer.setStencilCompareMask(0x00);
			uint32_t stencilColor = 0;
			//Draw portals of the main scene
			for (auto& gameobject : gameRoot.hGameObject.getAll()) {

				if (!gameobject.second->hasModule<ModulePortal>()) {
					continue; //Skip all gameobjects without portals
				}

				commandbuffer.setStencilWriteMask(++stencilColor); //Increase color for each portal

				const uint32_t offset = static_cast<uint32_t>(gameobject.first)* static_cast<uint32_t>(m_dynamicAlignment);

				ModuleGeometry* geometry = gameRoot.hGeometry.get<ModuleGeometry>(gameobject.second.get());

				commandbuffer.bindDescriptorSets(m_pipelines.mainDepth.getPipelineLayout(), descriptors[0].getDescriptorSet(), &offset);
				commandbuffer.bindVertexBuffers(geometry->getVertexBuffer().buffer);
				commandbuffer.bindIndexBuffers(geometry->getIndexBuffer().buffer);
				commandbuffer.drawIndexed(static_cast<uint32_t>(geometry->getIndexData().size()));
			}
		}

		commandbuffer.nextSubpass();

		commandbuffer.bindPipeline(m_pipelines.portalDepth);


		commandbuffer.nextSubpass();


		{
			//======================
			// Draw Skybox
			//======================
			commandbuffer.bindPipeline(m_pipelines.skybox);

			Skybox* skybox = gameRoot.hSkybox.get(0);
			ModuleGeometry* geometry = gameRoot.hGeometry.get<ModuleGeometry>(skybox->getGeoID());

			const uint32_t offset = (0);
			const uint32_t dynUboOffset = static_cast<uint32_t>(m_dynamicAlignment * 0);


			commandbuffer.bindDescriptorSets(m_pipelines.skybox.getPipelineLayout(), descriptors[1].getDescriptorSet(), &offset);
			commandbuffer.bindVertexBuffers(geometry->getVertexBuffer().buffer);
			commandbuffer.bindIndexBuffers(geometry->getIndexBuffer().buffer);
			commandbuffer.drawIndexed(static_cast<uint32_t>(geometry->getIndexData().size()));
		}
		{
			//======================
			// Draw Main Scene
			//======================
			commandbuffer.bindPipeline(m_pipelines.main);

			for (auto& gameobject : gameRoot.hGameObject.getAll()) {

				if (gameobject.second->hasModule<ModulePortal>()) {
					continue; //Skip all gameobjects without portals
				}

				const uint32_t offset = static_cast<uint32_t>(gameobject.first)* static_cast<uint32_t>(m_dynamicAlignment);

				ModuleGeometry* geometry = gameRoot.hGeometry.get<ModuleGeometry>(gameobject.second.get());

				commandbuffer.bindDescriptorSets(m_pipelines.main.getPipelineLayout(), descriptors[0].getDescriptorSet(), &offset);
				commandbuffer.bindVertexBuffers(geometry->getVertexBuffer().buffer);
				commandbuffer.bindIndexBuffers(geometry->getIndexBuffer().buffer);
				commandbuffer.drawIndexed(static_cast<uint32_t>(geometry->getIndexData().size()));
			}
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

void Renderer::updateUniformBuffer(GameRoot& gameRoot, const bool initial)
{
	Scene* scene = gameRoot.hScene.get(0);
	Camera* camera = gameRoot.hCamera.get(scene->m_activeCamera);

	if (initial) {
		MaterialUBO materialUBO;
		int i = 0;
		for (auto& materialPair : gameRoot.hMaterial.getAll()) {
			materialUBO.materials[i++] = materialPair.second->getMaterialBlock();
		}
		m_buffers.materialUBO.map();
		memcpy(m_buffers.materialUBO.mapped, &materialUBO, sizeof(MaterialUBO));
		m_buffers.materialUBO.unmap();

		m_buffers.mainUBO.map();
		m_buffers.mainUBODyn.map();
		m_buffers.skyboxUBODyn.map();
	}

	MainUBO ubo;
	ubo.proj = camera->getProjection();
	ubo.view = camera->getView();
	ubo.viewProj = ubo.proj * ubo.view;
	ubo.position = Vec4(camera->getPosition(), 1.0f);

	//m_buffers.mainUBO.map();
	memcpy(m_buffers.mainUBO.mapped, &ubo, sizeof(MainUBO));
	//m_buffers.mainUBO.unmap();

	MainUBODyn dynUBO;
	for (auto& gameObjectPair : gameRoot.hGameObject.getAll()) {
		ModuleTransformation* transform = gameRoot.hTransformation.get(gameObjectPair.second.get());

		dynUBO.modelMat = transform->getGlobalMat();
		
		if (gameObjectPair.second->hasModule<ModuleMaterial>()) {
			dynUBO.materialID = gameObjectPair.second->getModule<ModuleMaterial>();
		}

		void* ptr = static_cast<char*>(m_buffers.mainUBODyn.mapped) + (gameObjectPair.first * m_dynamicAlignment);
		memcpy(ptr, &dynUBO, sizeof(MainUBODyn));
		//m_buffers.mainUBODyn.unmap();
	}


	

	SkyboxUBODyn skyboxDynUBO;
	skyboxDynUBO.viewProj = camera->getProjection() * Mat4(1.0f);
	skyboxDynUBO.skyboxID = 0;
	void* ptr = static_cast<char*>(m_buffers.skyboxUBODyn.mapped) + (0 * m_dynamicAlignment);
	memcpy(ptr, &skyboxDynUBO, sizeof(SkyboxUBODyn));
	//m_buffers.skyboxUBODyn.unmap();
}


void Renderer::Destroy()
{
	return;
	m_shaders.main.Destroy();
	m_pipelines.main.Destroy();
	m_renderpass.Destroy();
	m_swapchain.Destroy();
}
