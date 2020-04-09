#include "Texture2D.hpp"

#ifndef STB_IMAGE_IMPLEMENTATION
	#define STB_IMAGE_IMPLEMENTATION
	#include <stb_image.h>
#endif // !STB_IMAGE_IMPLEMENTATION


Texture2D::Texture2D(const std::string& filename) : m_fileName(filename)
{
}

void Texture2D::setModuleID(const int32_t ID)
{
	m_moduleID = ID;
}

int32_t Texture2D::getModuleID() const
{
	return m_moduleID;
}

void Texture2D::setDebugName(const std::string& name)
{
	m_debugName = name;
}

std::string Texture2D::getDebugName() const
{
	return m_debugName;
}

void Texture2D::Init(const VkDevice& device, const VkPhysicalDevice& gpu, const Queue& queueGraphics)
{
	Texture::Init(device, gpu, queueGraphics);
	m_sampler.Init(device, gpu);
}

void Texture2D::createTexture(CommandBuffer& copyCMDBuffer)
{
	int width, height, depth;
	unsigned char* data = stbi_load(m_fileName.c_str(), &width, &height, &depth, STBI_rgb_alpha);

	if (data == nullptr) {
		ABORT_F("Failed to load Texture2D under %s", m_fileName.c_str());
	}

	//Convert to own variable names
	m_width = static_cast<uint32_t>(width);
	m_height  = static_cast<uint32_t>(height);
	m_depth = 4;

	const VkDeviceSize imageSize = static_cast<VkDeviceSize>(m_width * m_height * m_depth);

	Buffer stagingBuffer;

	Buffer::createBuffer(m_device, m_gpu,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		stagingBuffer,
		imageSize,
		data
	);

	stbi_image_free(data);

	const VkImageUsageFlags usageFlags = VK_IMAGE_USAGE_SAMPLED_BIT;
	const VkImageLayout finalTransitionLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

	m_image.create(m_device, m_gpu, m_width, m_height, m_mipLevels, m_format, usageFlags);

	VkBufferImageCopy region = {};
	region.bufferOffset = 0;
	region.bufferRowLength = 0;
	region.bufferImageHeight = 0;
	region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	region.imageSubresource.mipLevel = 0;// m_mipLevels;
	region.imageSubresource.baseArrayLayer = 0;
	region.imageSubresource.layerCount = 1;
	region.imageOffset = { 0, 0, 0 };
	region.imageExtent = { m_width, m_height, 1 };

	// Image barrier for optimal image (target)
	// Set initial layout for all array layers (faces) of the optimal (target) tiled texture
	VkImageSubresourceRange subresourceRange = {};
	subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	subresourceRange.baseMipLevel = 0;
	subresourceRange.levelCount = m_mipLevels;
	subresourceRange.layerCount = 1;

	copyCMDBuffer.beginCommandBuffer(true);

	Helper::setImageLayout(
		copyCMDBuffer.get(),
		m_image.getImage(),
		VK_IMAGE_LAYOUT_UNDEFINED,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		subresourceRange,
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
		VK_PIPELINE_STAGE_TRANSFER_BIT
	);

	copyCMDBuffer.copyBufferToImage(
		stagingBuffer.buffer,
		m_image.getImage(),
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		1,
		&region
	);

	// Change texture image layout to shader read after all faces have been copied
	Helper::setImageLayout(
		copyCMDBuffer.get(),
		m_image.getImage(),
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		subresourceRange,
		VK_PIPELINE_STAGE_TRANSFER_BIT,
		VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT);

	copyCMDBuffer.endCommandBuffer();

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &copyCMDBuffer.get();

	vkQueueSubmit(m_queueGraphics.getQueue(), 1, &submitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(m_queueGraphics.getQueue());

	m_imageView.create(m_device, m_image, VK_IMAGE_ASPECT_COLOR_BIT);

	stagingBuffer.destroy();
}

void Texture2D::createSampler()
{
	m_sampler.create();
}

Sampler& Texture2D::getSampler()
{
	return m_sampler;
}

VkDescriptorImageInfo Texture2D::getDescriptorImageInfo()
{
	VkDescriptorImageInfo info = {};
	info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	info.imageView = m_imageView.get();
	info.sampler = m_sampler.getSampler();

	return info;
}
