#pragma once

#include <loguru.hpp>
#include <vulkan/vulkan.h>

#include "Image.hpp"
#include "ImageView.hpp"
#include "Queue.hpp"

class Texture
{
protected:
	VkDevice m_device;
	VkPhysicalDevice m_gpu;
	Queue m_queueGraphics;

	Image m_image;
	ImageView m_imageView;

	uint32_t m_width = 0;
	uint32_t m_height = 0;
	uint32_t m_depth = 0;
	uint32_t m_faceCount = 1;
	uint32_t m_arrays = 1;
	uint32_t m_mipLevels = 1;

public:
	virtual void Init(const VkDevice& device, const VkPhysicalDevice& gpu, const Queue& queueGraphics);
	void createEmptyDepthImage(const VkFormat format, const uint32_t width, const uint32_t height, const uint32_t mipLevels, const VkImageUsageFlags usageFlags, const uint32_t faces = 1);
	Image& getImage();
	ImageView& getImageView();
};

