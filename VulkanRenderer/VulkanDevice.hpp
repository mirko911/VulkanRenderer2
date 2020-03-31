#pragma once
#include <vector>

#include <loguru.hpp>
#include <vulkan/vulkan.h>

class VulkanDevice
{
private:
	VkInstance m_instance = VK_NULL_HANDLE;
	VkPhysicalDevice m_gpu = VK_NULL_HANDLE;
	VkDevice m_device = VK_NULL_HANDLE;
	VkSurfaceKHR m_surface = VK_NULL_HANDLE;

	std::vector<const char*> m_extensionsEnabled;
	std::vector<const char*> m_validationLayersEnabled;

	//Check if an extension name (needle) exists in a vector of extensions (haystack)
	bool hasExtensionProperty(const char* needle, const std::vector<VkExtensionProperties>& haystack);
	bool hasLayerProperty(const char* needle, const std::vector<VkLayerProperties>& haystack);
public:
	void createInstance(const std::vector<const char*>& glfwExtensions);

	void destroyDevice();
};

