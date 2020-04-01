#include "Texture.hpp"

void Texture::Init(const VkDevice& device, const VkPhysicalDevice& gpu, const Queue& queueGraphics)
{
	m_device = device;
	m_gpu = gpu;
	m_queueGraphics = queueGraphics;
}

void Texture::createEmptyDepthImage(const VkFormat format, const uint32_t width, const uint32_t height, const uint32_t mipLevels, const VkImageUsageFlags usageFlags, const uint32_t faces)
{
	m_image.create(m_device, m_gpu, width, height, mipLevels, format, usageFlags);

	m_imageView.create(m_device, m_image, VK_IMAGE_ASPECT_DEPTH_BIT);
}

Image& Texture::getImage()
{
	return m_image;
}

ImageView& Texture::getImageView()
{
	return m_imageView;
}
