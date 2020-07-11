#include "RendererFont.hpp"


#include <fstream>
#include <iostream>

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

void RendererFont::loadFont()
{
	const std::string filename = "fonts//Exo2-Regular.ttf";
	std::ifstream file(filename, std::ios::binary | std::ios::ate);
	const std::streamsize size = file.tellg();
	ttf_buffer.resize(1 << 20);
	file.seekg(0, std::ios::beg);

	if (size > (1 << 20)) {
		LOG_F(ERROR, "Font file to big for buffer %s", filename.c_str());

	}

	if (!file.read(reinterpret_cast<char*>(ttf_buffer.data()), size)) {
		LOG_F(ERROR, "Failed to load font %s", filename.c_str());
	}

	file.close();

	stbtt_InitFont(&font, ttf_buffer.data(), 0);
	scale = stbtt_ScaleForPixelHeight(&font, 15);
	int ascent = 0;
	stbtt_GetFontVMetrics(&font, &ascent, 0, 0);
	baseline = (int)(ascent * scale);


	stbtt_BakeFontBitmap(ttf_buffer.data(), 0, 32.0f, temp_bitmap.data(), 512, 512, 32, 96, cdata.data());
}

void RendererFont::Init(VulkanDevice& device, GameRoot& gameRoot)
{
	//===============================================================================
	//Init Shader
	//===============================================================================
	m_shader.Init(device.getDevice());
	m_shader.addShaderStage(VK_SHADER_STAGE_VERTEX_BIT, "shaders/font.vert.spv");
	m_shader.addShaderStage(VK_SHADER_STAGE_FRAGMENT_BIT, "shaders/font.frag.spv");

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

	VkAttachmentDescription attachments[2] = {};

	// Color attachment
	attachments[0].format = VK_FORMAT_B8G8R8A8_UNORM;
	attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
	// Don't clear the framebuffer (like the renderpass from the example does)
	attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
	attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	attachments[0].initialLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	attachments[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	// Depth attachment
	attachments[1].format = optimalDepthFormat;
	attachments[1].samples = VK_SAMPLE_COUNT_1_BIT;
	attachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	attachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	attachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	attachments[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	attachments[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkAttachmentReference colorReference = {};
	colorReference.attachment = 0;
	colorReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkAttachmentReference depthReference = {};
	depthReference.attachment = 1;
	depthReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	// Use subpass dependencies for image layout transitions
	VkSubpassDependency subpassDependencies[2] = {};

	// Transition from final to initial (VK_SUBPASS_EXTERNAL refers to all commmands executed outside of the actual renderpass)
	subpassDependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
	subpassDependencies[0].dstSubpass = 0;
	subpassDependencies[0].srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
	subpassDependencies[0].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	subpassDependencies[0].srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
	subpassDependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	subpassDependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

	// Transition from initial to final
	subpassDependencies[1].srcSubpass = 0;
	subpassDependencies[1].dstSubpass = VK_SUBPASS_EXTERNAL;
	subpassDependencies[1].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	subpassDependencies[1].dstStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
	subpassDependencies[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	subpassDependencies[1].dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
	subpassDependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

	VkSubpassDescription subpassDescription = {};
	subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpassDescription.flags = 0;
	subpassDescription.inputAttachmentCount = 0;
	subpassDescription.pInputAttachments = NULL;
	subpassDescription.colorAttachmentCount = 1;
	subpassDescription.pColorAttachments = &colorReference;
	subpassDescription.pResolveAttachments = NULL;
	subpassDescription.pDepthStencilAttachment = &depthReference;
	subpassDescription.preserveAttachmentCount = 0;
	subpassDescription.pPreserveAttachments = NULL;

	m_renderpass.addAttachmentCustom(attachments[0]);
	m_renderpass.addAttachmentCustom(attachments[1]);
	m_renderpass.addSubpassCustom(subpassDescription);
	m_renderpass.addSubpassDependencyCustom(subpassDependencies[0]);
	m_renderpass.addSubpassDependencyCustom(subpassDependencies[1]);
	m_renderpass.setDimensions(1280, 720);
	m_renderpass.createRenderpass();

	const uint32_t textureSize = 512;
	temp_bitmap.resize(textureSize * textureSize);
	cdata.resize(96); // ASCII 32..126 is 95 glyphs
	loadFont();

	CommandBuffer copyCMDBuffer = device.getCommandPool().allocateCommandBuffer();
	m_fontTexture.setSize(textureSize, textureSize);
	m_fontTexture.Init(device.getDevice(), device.getGPU(), device.getGraphicsQueue());
	m_fontTexture.uploadData(copyCMDBuffer, temp_bitmap);
	m_fontTexture.createSampler();

	Descriptor descriptor;
	descriptor.Init(device.getDevice());
	descriptor.addLayoutBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 1);
	descriptor.createDescriptorSetLayout();

	m_fontDescriptors = { descriptor };

	DescriptorPool descriptorPool;
	descriptorPool.Init(device.getDevice(), device.getGPU());
	descriptorPool.create(m_fontDescriptors);
	descriptorPool.allocateDescriptorSets(m_fontDescriptors);

	VkDescriptorImageInfo texDescriptor = m_fontTexture.getDescriptorImageInfo();

	m_fontDescriptors[0].writeSet(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, { texDescriptor });

	//===============================================================================
	//Init Pipeline
	//===============================================================================
	std::vector<VkDescriptorSetLayout> layoutInfoMain = { m_fontDescriptors[0].getDescriptorSetLayout() };

	m_pipeline.Init(device.getDevice(), m_renderpass, m_shader);
	m_pipeline.addDynamicState(VK_DYNAMIC_STATE_VIEWPORT);
	m_pipeline.addDynamicState(VK_DYNAMIC_STATE_SCISSOR);
	m_pipeline.getDepthStencil().stencilTestEnable = VK_FALSE;
	m_pipeline.getDepthStencil().depthTestEnable = VK_FALSE;
	m_pipeline.getDepthStencil().depthWriteEnable = VK_FALSE;
	m_pipeline.createLayoutInfo(layoutInfoMain);
	m_pipeline.createPipeline(0);

	const VkDeviceSize bufferSize = FONT_MAX_CHAR_COUNT * sizeof(glm::vec4);
	Buffer::createBuffer(device.getDevice(), device.getGPU(),
		VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		m_vertexBuffer,
		bufferSize);

	m_device = device;
	m_commandBuffers.reserve(3); //@TODO: use swapchain for image count
	for (int i = 0; i < 3; i++) {
		CommandBuffer commandbuffer = m_device.getCommandPool().allocateCommandBuffer();
		m_commandBuffers.emplace_back(std::move(commandbuffer));
	}

}

void RendererFont::Draw(GameRoot& gameRoot)
{

}

void RendererFont::Render(GameRoot& gameRoot)
{
}

void RendererFont::updateUniformBuffer(GameRoot& gameRoot, const bool initial)
{
}

void RendererFont::Destroy()
{
}

CommandBuffer& RendererFont::getCommandBuffer()
{
	return m_commandBuffers[0];
}

void RendererFont::linkFrameBuffers(std::vector<VkFramebuffer>& frameBuffers)
{
	m_renderpass.setFrameBuffers(frameBuffers);
}

void RendererFont::updateCommandBuffer()
{

	const VkClearColorValue color = { 0.0f, 0.0f, 0.0f, 0.0f };

	
	//===============================================================================
	//Record command buffers (draw calls)
	//===============================================================================
	for (uint32_t i = 0; i < 3; i++) {

		CommandBuffer commandbuffer = m_device.getCommandPool().allocateCommandBuffer();
		m_commandBuffers[i] = commandbuffer;

		commandbuffer.beginCommandBuffer();

		auto beginInfo = m_renderpass.getBeginInfo(color, i);
		commandbuffer.beginRenderPass(beginInfo);

		VkViewport viewport{};
		viewport.width = m_renderpass.getWidth();
		viewport.height = m_renderpass.getHeight();
		viewport.minDepth = 0;
		viewport.maxDepth = 1;

		VkRect2D scissor{};
		scissor.extent.width = m_renderpass.getWidth();
		scissor.extent.height = m_renderpass.getHeight();
		scissor.offset.x = 0;
		scissor.offset.y = 0;

		VkDeviceSize offsets = 0;

		vkCmdSetViewport(commandbuffer.get(), 0, 1, &viewport);
		vkCmdSetScissor(commandbuffer.get(), 0, 1, &scissor);

		vkCmdBindVertexBuffers(commandbuffer.get(), 0, 1, &m_vertexBuffer.buffer, &offsets);
		vkCmdBindVertexBuffers(commandbuffer.get(), 1, 1, &m_vertexBuffer.buffer, &offsets);
		commandbuffer.bindPipeline(m_pipeline);
		commandbuffer.bindDescriptorSets(m_pipeline.getPipelineLayout(), m_fontDescriptors[0].getDescriptorSet());

		for (uint32_t j = 0; j < numLetters; j++) {
			vkCmdDraw(commandbuffer.get(), 4, 1, j * 4, 0);
		}

		commandbuffer.endRenderPass();
		commandbuffer.endCommandBuffer();
	}
}

void RendererFont::mapVertexBuffer()
{
	m_vertexBuffer.map(VK_WHOLE_SIZE, 0);
	mapped = reinterpret_cast<Vec4*>(m_vertexBuffer.mapped);
	numLetters = 0;
}

void RendererFont::unmapVertexBuffer()
{
	m_vertexBuffer.unmap();
	updateCommandBuffer();
}

void RendererFont::addText(const std::string& text, const float x, const float y, const TextAlign align)
{
	for (auto letter : text) {
		if (letter < 32 && letter >= 128) {
			continue;
		}

		/*int advance, lsb, x0, y0, x1, y1;

		float x_shift = 0 - (float)floor(0);

		stbtt_GetCodepointHMetrics(&font, letter, &advance, &lsb);
		stbtt_GetCodepointBitmapBoxSubpixel(&font, letter, scale, scale, x_shift, 0, &x0, &y0, &x1, &y1);
		stbtt_MakeCodepointBitmapSubpixel(&font, &screen[baseline + y0][(int)0 + x0], x1 - x0, y1 - y0, 79, scale, scale, x_shift, 0, letter);
		*/
		float x = 0;
		float y = 0;

		stbtt_aligned_quad q;
		stbtt_GetBakedQuad(cdata.data(), 512, 512, letter - 32, &x, &y, &q, 1);

		q.x0 /= 1280.0 / 2;
		q.x1 /= 1280.0 / 2;
		q.y0 /= 720.0 / 2;
		q.y1 /= 720.0 / 2;


		mapped->x =  q.x0;
		mapped->y =  q.y0;
		mapped->z = q.s0;
		mapped->w = q.t0;
		mapped++;

		mapped->x = q.x1;
		mapped->y = q.y0;
		mapped->z = q.s1;
		mapped->w = q.t0;
		mapped++;

		mapped->x = q.x0;
		mapped->y = q.y1;
		mapped->z = q.s0;
		mapped->w = q.t1;
		mapped++;

		mapped->x = q.x1;
		mapped->y = q.y1;
		mapped->z = q.s1;
		mapped->w = q.t1;
		mapped++;


		numLetters++;
	}
}
