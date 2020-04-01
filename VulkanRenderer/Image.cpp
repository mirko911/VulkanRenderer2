#include "Image.hpp"

void Image::create(const VkDevice& device, const VkPhysicalDevice& gpu, const uint32_t width, const uint32_t height, const uint32_t mipLevels, const VkFormat format, const VkImageUsageFlags usage, const uint32_t arrayLayers)
{
	m_width = width;
	m_height = height;
	m_miplevels = mipLevels;
	m_format = format;
	m_arrays = arrayLayers;

	VkImageCreateInfo imageInfo = {};
	imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageInfo.imageType = VK_IMAGE_TYPE_2D;
	imageInfo.format = format;
	imageInfo.extent.width = width;
	imageInfo.extent.height = height;
	imageInfo.extent.depth = 1;
	imageInfo.mipLevels = mipLevels;
	imageInfo.arrayLayers = arrayLayers; //facecount * arrays;
	imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;//tiling;
	imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | usage;
	imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

	if (arrayLayers == 6) {
		imageInfo.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;
	}

	if (vkCreateImage(device, &imageInfo, nullptr, &m_image) != VK_SUCCESS) {
		throw std::runtime_error("failed to create image!");
	}

	VkMemoryRequirements memRequirements;
	vkGetImageMemoryRequirements(device, m_image, &memRequirements);

	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = VulkanDevice::findMemoryType(gpu, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

	if (vkAllocateMemory(device, &allocInfo, nullptr, &m_memory) != VK_SUCCESS) {
		ABORT_F("Failed to allocate image memory");
	}

	if (vkBindImageMemory(device, m_image, m_memory, 0) != VK_SUCCESS) {
		ABORT_F("Failed to bind image memory");
	};
}

VkImage& Image::getImage()
{
	return m_image;
}

VkFormat Image::getFormat() const
{
	return m_format;
}

uint32_t Image::getMipLevels() const
{
	return m_miplevels;
}
