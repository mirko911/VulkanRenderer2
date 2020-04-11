#include "TextureCubemap.hpp"

#ifndef STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif // !STB_IMAGE_IMPLEMENTATION

void TextureCubemap::setModuleID(const int32_t ID)
{
	m_moduleID = ID;
}

int32_t TextureCubemap::getModuleID() const
{
	return m_moduleID;
}

void TextureCubemap::setDebugName(const std::string& name)
{
	m_debugName = name;
}

std::string TextureCubemap::getDebugName() const
{
	return m_debugName;
}

TextureCubemap::TextureCubemap(const std::string& filename, const std::string& fileExtension)
	: m_fileName(filename), m_fileExtension(fileExtension)
{
}

void TextureCubemap::Init(const VkDevice& device, const VkPhysicalDevice& gpu, const Queue& ququeGraphics)
{
	Texture::Init(device, gpu, ququeGraphics);
	m_sampler.Init(device, gpu);
}

void TextureCubemap::createTexture(CommandBuffer& copyCMDBuffer)
{
	std::array<unsigned char*, 6> data = {nullptr};
	int width, height, depth;
	int number_pixels = 0; //Check if all images have the same dimension

	for (size_t i = 0; i < 6; i++) {
		std::string completeFileName = m_fileName + "_" + m_names[i] + "." + m_fileExtension;

		data[i] = stbi_load(completeFileName.c_str(), &width, &height, &depth, STBI_rgb_alpha);
		if (data[i] == nullptr) {
			ABORT_F("Failed to load TextureCubemap under %s", completeFileName.c_str());
		}

		if (number_pixels != 0 && (width * height) != number_pixels) {
			ABORT_F("TextureCubemap has different dimensions %s", completeFileName.c_str());
		}
		number_pixels = width * height;
	}

	//Convert to own variable names
	m_width = static_cast<uint32_t>(width);
	m_height = static_cast<uint32_t>(height);
	m_depth = 4;

	//Calculate the image size and the layer size.
	const VkDeviceSize layerSize = width * height * 4; //4 since I always load my textures with an alpha channel, and multiply it by 6 because the image must have 6 layers.
	const VkDeviceSize imageSize = layerSize * 6; //This is just the size of each layer.

	Buffer stagingBuffer;

	Buffer::createBuffer(m_device, m_gpu,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		stagingBuffer, imageSize
	);

	stagingBuffer.map();
	for (int i = 0; i < 6; i++) {
		void* mapped = reinterpret_cast<char*>(stagingBuffer.mapped) + (i * layerSize);
		memcpy(mapped, data[i], layerSize);
		stbi_image_free(data[i]);
	}
	stagingBuffer.unmap();

	m_image.create(m_device, m_gpu, m_width, m_height, m_mipLevels, m_format, VK_IMAGE_USAGE_SAMPLED_BIT, 6);

	// Setup buffer copy regions for each face including all of its miplevels
	std::vector<VkBufferImageCopy> bufferCopyRegions;
	VkDeviceSize offset = 0;

	for (uint32_t face = 0; face < 6; face++)
	{
		for (uint32_t level = 0; level < m_mipLevels; level++)
		{
			// Calculate offset into staging buffer for the current mip level and face

			offset = layerSize * face;

			VkBufferImageCopy bufferCopyRegion = {};
			bufferCopyRegion.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			bufferCopyRegion.imageSubresource.mipLevel = level;
			bufferCopyRegion.imageSubresource.baseArrayLayer = face;
			bufferCopyRegion.imageSubresource.layerCount = 1;
			bufferCopyRegion.imageExtent.width = width >> level;
			bufferCopyRegion.imageExtent.height = height >> level;
			bufferCopyRegion.imageExtent.depth = 1;
			bufferCopyRegion.bufferOffset = offset;
			bufferCopyRegions.push_back(bufferCopyRegion);
		}
	}

	// Image barrier for optimal image (target)
	// Set initial layout for all array layers (faces) of the optimal (target) tiled texture
	VkImageSubresourceRange subresourceRange = {};
	subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	subresourceRange.baseMipLevel = 0;
	subresourceRange.levelCount = m_mipLevels;
	subresourceRange.layerCount = 6;

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
		static_cast<uint32_t>(bufferCopyRegions.size()),
		bufferCopyRegions.data()
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

void TextureCubemap::createSampler()
{
	m_sampler.create();
}

Sampler& TextureCubemap::getSampler()
{
	return m_sampler;
}

VkDescriptorImageInfo TextureCubemap::getDescriptorImageInfo()
{
	VkDescriptorImageInfo info = {};
	info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	info.imageView = m_imageView.get();
	info.sampler = m_sampler.getSampler();

	return info;
}
