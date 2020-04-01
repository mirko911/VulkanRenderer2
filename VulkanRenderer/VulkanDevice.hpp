#pragma once
#include <vector>

#include <loguru.hpp>
#include <vulkan/vulkan.h>

#include "defintions.hpp"
#include "Window.hpp"
#include "Queue.hpp"
class VulkanDevice
{
private:
	VkInstance m_instance = VK_NULL_HANDLE;
	VkPhysicalDevice m_gpu = VK_NULL_HANDLE;
	VkDevice m_device = VK_NULL_HANDLE;
	VkSurfaceKHR m_surface = VK_NULL_HANDLE;
	Queue m_queueGraphics;
	Queue m_queuePresent;

	std::vector<const char*> m_extensionsEnabled;
	std::vector<const char*> m_validationLayersEnabled;

	//Check if an extension name (needle) exists in a vector of extensions (haystack)
	bool hasExtensionProperty(const char* needle, const std::vector<VkExtensionProperties>& haystack);
	bool hasLayerProperty(const char* needle, const std::vector<VkLayerProperties>& haystack);
	QueueFamilyIndices getQueueFamilyProperties();
public:
	void createInstance(const std::vector<const char*>& glfwExtensions);
	void createSurface(GLFWwindow* window);
	void createDevice();
	void destroyDevice();
	VkInstance& getInstance();
	VkDevice& getDevice();
	VkPhysicalDevice &getGPU();
	VkSurfaceKHR& getSurface();
	Queue& getGraphicsQueue();
	Queue& getPresentQueue();
};

