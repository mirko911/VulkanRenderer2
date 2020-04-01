#include "Swapchain.hpp"

VkSurfaceFormatKHR Swapchain::chooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
	for (const auto& availableFormat : availableFormats) {
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return availableFormat;
		}
	}

	return availableFormats[0];
}

VkPresentModeKHR Swapchain::choosePresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
{
	for (const auto& availablePresentMode : availablePresentModes) {
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			return availablePresentMode;
		}
	}

	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D Swapchain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
{
	if (capabilities.currentExtent.width != UINT32_MAX) {
		return capabilities.currentExtent;
	}
	else {
		int width = 1280, height = 720;
		//fwGetFramebufferSize(window, &width, &height);

		VkExtent2D actualExtent = {
			static_cast<uint32_t>(width),
			static_cast<uint32_t>(height)
		};


		actualExtent.width = (std::max)(capabilities.minImageExtent.width, (std::min)(capabilities.maxImageExtent.width, actualExtent.width));
		actualExtent.height = (std::max)(capabilities.minImageExtent.height, (std::min)(capabilities.maxImageExtent.height, actualExtent.height));

		return actualExtent;
	}
}

void Swapchain::Init(const VkDevice& device, const VkPhysicalDevice& gpu, const VkSurfaceKHR& surface, const Queue& graphcQueue, const Queue& presentQueue, const uint32_t width, const uint32_t height)
{
	m_device = device;
	m_gpu = gpu;
	m_surface = surface;
	m_queueGraphics = graphcQueue;
	m_queuePresent = presentQueue;
	m_width = width;
	m_height = height;
}

void Swapchain::Destroy()
{
	for (ImageView& imageView : m_imageViews) {
		vkDestroyImageView(m_device, imageView.get(), nullptr);
	}
	for (VkImage& image : m_images) {
		vkDestroyImage(m_device, image, nullptr);
	}
	vkDestroySwapchainKHR(m_device, m_swapchain, nullptr);
}

void Swapchain::create()
{
	// Get the basic surface properties of the physical device
	uint32_t surfaceCount = 0;

	VkSurfaceCapabilitiesKHR capabilities;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_gpu, m_surface, &capabilities);

	std::vector<VkSurfaceFormatKHR> surfaceFormats;
	uint32_t surfaceFormatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(m_gpu, m_surface, &surfaceFormatCount, nullptr);
	surfaceFormats.resize(surfaceFormatCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(m_gpu, m_surface, &surfaceFormatCount, surfaceFormats.data());

	std::vector<VkPresentModeKHR> presentModes;
	uint32_t presentModesCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(m_gpu, m_surface, &presentModesCount, nullptr);
	presentModes.resize(presentModesCount);
	vkGetPhysicalDeviceSurfacePresentModesKHR(m_gpu, m_surface, &presentModesCount, presentModes.data());

	// make sure that we have suitable swap chain extensions available before continuing
	if (surfaceFormats.empty() || presentModes.empty()) {
		ABORT_F("Unable to locate swapchain surfaces or presentmodes");
	}

	surfaceFormat = chooseSurfaceFormat(surfaceFormats);
	VkPresentModeKHR presentMode = choosePresentMode(presentModes);
	m_extend = chooseSwapExtent(capabilities);

	uint32_t imageCount = capabilities.minImageCount + 1; // adding one as we would like to implement triple buffering
	if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount) {
		imageCount = capabilities.maxImageCount;
	}

	std::vector<uint32_t> queueFamilyIndicies;
	VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (m_queueGraphics.getIndex() != m_queuePresent.getIndex()) {
		sharingMode = VK_SHARING_MODE_CONCURRENT;
		queueFamilyIndicies.push_back(m_queueGraphics.getIndex());
		queueFamilyIndicies.push_back(m_queuePresent.getIndex());
	}

	VkSwapchainCreateInfoKHR createInfo = {};
	createInfo.pNext = {};
	createInfo.surface = m_surface;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	createInfo.queueFamilyIndexCount = static_cast<uint32_t>(queueFamilyIndicies.size());
	createInfo.pQueueFamilyIndices = queueFamilyIndicies.data();
	createInfo.imageExtent = m_extend;
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.imageSharingMode = sharingMode;
	createInfo.preTransform = capabilities.currentTransform;
	createInfo.minImageCount = imageCount;
	createInfo.imageArrayLayers = 1;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	if (vkCreateSwapchainKHR(m_device, &createInfo, nullptr, &m_swapchain) != VK_SUCCESS) {
		ABORT_F("Failed to create swapchain");
	}

	// Get the image loactions created when creating the swap chains
	;
	vkGetSwapchainImagesKHR(m_device, m_swapchain, &m_imageCount, nullptr);
	m_images.resize(m_imageCount);
	vkGetSwapchainImagesKHR(m_device, m_swapchain, &m_imageCount, m_images.data());

}

void Swapchain::createImageViews()
{
	m_imageViews.resize(m_imageCount);

	for (size_t i = 0; i < m_images.size(); i++) {
		m_imageViews[i].create(m_device, m_images[i], surfaceFormat.format, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_VIEW_TYPE_2D);
	}
}

uint32_t Swapchain::getImageCount() const
{
	return m_imageCount;
}

uint32_t Swapchain::getImageIndex() const
{
	return m_imageIndex;
}

std::vector<ImageView>& Swapchain::getImageViews()
{
	return m_imageViews;
}

std::vector<VkImage>& Swapchain::getImages()
{
	return m_images;
}

void Swapchain::beginFrame(const VkSemaphore& semaphore)
{
	VkResult result = vkAcquireNextImageKHR(m_device, m_swapchain, std::numeric_limits<uint64_t>::max(), semaphore, VK_NULL_HANDLE, &m_imageIndex);

	if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
		throw std::runtime_error("failed to acquire swap chain image!");
	}
}

void Swapchain::submitFrame(const VkSemaphore& signalSemaphore)
{
	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = &signalSemaphore;

	VkSwapchainKHR swapChains[] = { m_swapchain };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = &m_imageIndex;

	vkQueuePresentKHR(m_queuePresent.getQueue(), &presentInfo);

}
