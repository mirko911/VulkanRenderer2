#pragma once

#include <algorithm>

#include <loguru.hpp>
#include <vulkan/vulkan.hpp>

#include "Queue.hpp"

class Swapchain
{
private:
	VkDevice m_device = VK_NULL_HANDLE;
	VkPhysicalDevice m_gpu = VK_NULL_HANDLE;
	VkSurfaceKHR m_surface = VK_NULL_HANDLE;
	VkSwapchainKHR m_swapchain = VK_NULL_HANDLE;

	Queue m_queueGraphics;
	Queue m_queuePresent;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_imageCount;

	std::vector<VkImage> m_images;
	std::vector<VkImageView> m_imageViews;

	VkSurfaceFormatKHR surfaceFormat;
	VkExtent2D m_extend;

	VkSurfaceFormatKHR chooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR choosePresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
public:
	void Init(const VkDevice& device, const VkPhysicalDevice& gpu, const VkSurfaceKHR& surface, const Queue& graphcQueue, const Queue& presentQueue, const uint32_t width, const uint32_t height);
	void Destroy();
	void create();
	void createImageViews();
};

