#include "TextureFont.hpp"


TextureFont::TextureFont()
{
}

void TextureFont::setModuleID(const int32_t ID)
{
	m_moduleID = ID;
}

int32_t TextureFont::getModuleID() const
{
	return m_moduleID;
}

void TextureFont::setDebugName(const std::string& name)
{
	m_debugName = name;
}

std::string TextureFont::getDebugName() const
{
	return m_debugName;
}

void TextureFont::Init(const VkDevice& device, const VkPhysicalDevice& gpu, const Queue& queueGraphics)
{
	Texture::Init(device, gpu, queueGraphics);
	m_image.create(m_device, m_gpu, m_width, m_height, 1, VK_FORMAT_R8_UNORM, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT);
	m_sampler.Init(device, gpu);

}

void TextureFont::setSize(const uint32_t width, const uint32_t height)
{
	m_width = width;
	m_height = height;
}

void TextureFont::uploadData(CommandBuffer& copyCMDBuffer, std::vector<unsigned char>& data) {

	Buffer stagingBuffer;

	//sharingMode = VK_SHARING_MODE_EXCLUSIVE
	Buffer::createBuffer(m_device, m_gpu,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		stagingBuffer,
		data.size(),
		data.data()
	);

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


	copyCMDBuffer.beginCommandBuffer(true);

	Helper::setImageLayout(
		copyCMDBuffer.get(),
		m_image.getImage(),
		VK_IMAGE_ASPECT_COLOR_BIT,
		VK_IMAGE_LAYOUT_UNDEFINED,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
	);

	copyCMDBuffer.copyBufferToImage(
		stagingBuffer.buffer,
		m_image.getImage(),
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		1,
		&region
	);

	Helper::setImageLayout(
		copyCMDBuffer.get(),
		m_image.getImage(),
		VK_IMAGE_ASPECT_COLOR_BIT,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
	);

	copyCMDBuffer.endCommandBuffer();

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &copyCMDBuffer.get();

	vkQueueSubmit(m_queueGraphics.getQueue(), 1, &submitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(m_queueGraphics.getQueue());

	m_imageView.create(m_device, m_image, VK_IMAGE_ASPECT_COLOR_BIT);

	stagingBuffer.destroy();

	m_imageView.create(m_device, m_image, VK_IMAGE_ASPECT_COLOR_BIT);

}

void TextureFont::createSampler()
{
	m_sampler.create();
}

Sampler& TextureFont::getSampler()
{
	return m_sampler;
}

VkDescriptorImageInfo TextureFont::getDescriptorImageInfo()
{
	VkDescriptorImageInfo info = {};
	info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	info.imageView = m_imageView.get();
	info.sampler = m_sampler.getSampler();

	return info;
}
