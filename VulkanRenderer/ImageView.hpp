#pragma once

#include <loguru.hpp>
#include <vulkan/vulkan.h>

class ImageView
{
private:
	VkImageView m_imageView;
public:
	void create(VkDevice& device, const VkImage& image, const VkFormat format, const VkImageAspectFlags aspectFlags, const uint32_t mipLevels);
	VkImageView& get();
};

