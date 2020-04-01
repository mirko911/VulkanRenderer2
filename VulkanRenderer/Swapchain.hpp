#pragma once

#include <algorithm>

#include <loguru.hpp>
#include <vulkan/vulkan.hpp>

#include "ImageView.hpp"
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

	uint32_t m_imageIndex;
	std::vector<VkImage> m_images;
	std::vector<ImageView> m_imageViews;

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
	uint32_t getImageCount() const;
	uint32_t getImageIndex() const;
	std::vector<ImageView>& getImageViews();
	std::vector<VkImage>& getImages();
	void beginFrame(const VkSemaphore& semaphore);
	void submitFrame(const VkSemaphore& presentSemaphore);
};

