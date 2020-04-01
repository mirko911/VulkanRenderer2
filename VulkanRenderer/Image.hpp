#pragma once
#include <loguru.hpp>
#include <vulkan/vulkan.hpp>

#include "VulkanDevice.hpp"
class Image
{
private:
	VkDevice m_device = VK_NULL_HANDLE;
	VkImage m_image = VK_NULL_HANDLE;
	VkDeviceMemory m_memory = VK_NULL_HANDLE;
	VkFormat m_format;

	uint32_t m_width = 0;
	uint32_t m_height = 0;
	uint32_t m_miplevels = 1;
	uint32_t m_faceCount = 1;
	uint32_t m_arrays = 1;
public:
	void create(const VkDevice& device, const VkPhysicalDevice& gpu, const uint32_t width,
		const uint32_t height, const  uint32_t mipLevels, const VkFormat format,
		const VkImageUsageFlags usage, const uint32_t arrayLayers = 1);
	VkImage& getImage();
	VkFormat getFormat() const;
};

