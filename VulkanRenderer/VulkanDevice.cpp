#include "VulkanDevice.hpp"

bool VulkanDevice::hasExtensionProperty(const char* needle, const std::vector<VkExtensionProperties>& haystack)
{
	for (const VkExtensionProperties& extension : haystack) {
		if (std::strcmp(needle, extension.extensionName) == 0) {
			return true;
		}
	}

	return false;
}

bool VulkanDevice::hasLayerProperty(const char* needle, const std::vector<VkLayerProperties>& haystack)
{
	for (const VkLayerProperties& extension : haystack) {
		if (std::strcmp(needle, extension.layerName) == 0) {
			return true;
		}
	}

	return false;
}

void VulkanDevice::createInstance(const std::vector<const char*>& glfwExtensions)
{
	LOG_F(INFO, "[VulkanDevice] Create Instance");

	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "VulkanRenderer";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "MyEngine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_2;

	//Queue for available extensions
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> instanceExtensionProperties(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, instanceExtensionProperties.data());


	LOG_F(INFO, "Available instance extensions:");
	for (const VkExtensionProperties& extensionProperties : instanceExtensionProperties) {
		LOG_F(INFO, "\t %s (%i)", extensionProperties.extensionName, extensionProperties.specVersion);
	}


	for (const char* glfwExtension : glfwExtensions) {
		if (!hasExtensionProperty(glfwExtension, instanceExtensionProperties)) {
			ABORT_F("Unable to find extension %s in instanceExtensionProperties", glfwExtension);
		}
	}

	//Add all glfw extensions to list of enabled extensions
	m_extensionsEnabled.insert(m_extensionsEnabled.end(), glfwExtensions.begin(), glfwExtensions.end());

	//Check for some optional extensions
	if (hasExtensionProperty(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME, instanceExtensionProperties)) {
		m_extensionsEnabled.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
	}
	else {
		LOG_F(WARNING, "Unable to find extension %s in instanceExtensionProperties", VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
	}

	if (hasExtensionProperty(VK_KHR_EXTERNAL_MEMORY_CAPABILITIES_EXTENSION_NAME, instanceExtensionProperties)) {
		m_extensionsEnabled.push_back(VK_KHR_EXTERNAL_MEMORY_CAPABILITIES_EXTENSION_NAME);
	}
	else {
		LOG_F(WARNING, "Unable to find extension %s in instanceExtensionProperties", VK_KHR_EXTERNAL_MEMORY_CAPABILITIES_EXTENSION_NAME);
	}

	if (hasExtensionProperty(VK_KHR_EXTERNAL_SEMAPHORE_CAPABILITIES_EXTENSION_NAME, instanceExtensionProperties)) {
		m_extensionsEnabled.push_back(VK_KHR_EXTERNAL_SEMAPHORE_CAPABILITIES_EXTENSION_NAME);
	}
	else {
		LOG_F(WARNING, "Unable to find extension %s in instanceExtensionProperties", VK_KHR_EXTERNAL_SEMAPHORE_CAPABILITIES_EXTENSION_NAME);
	}

	if (hasExtensionProperty(VK_EXT_DEBUG_UTILS_EXTENSION_NAME, instanceExtensionProperties)) {
		m_extensionsEnabled.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}
	else {
		LOG_F(WARNING, "Unable to find extension %s in instanceExtensionProperties", VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}
	
	uint32_t instanceLayerCount;
	vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr);
	std::vector<VkLayerProperties> instanceLayerProperties(instanceLayerCount);
	vkEnumerateInstanceLayerProperties(&instanceLayerCount, instanceLayerProperties.data());

	LOG_F(INFO, "Available validation layers:");
	for (const VkLayerProperties& layerProperties : instanceLayerProperties) {
		LOG_F(INFO, "\t %s (%i)", layerProperties.layerName, layerProperties.specVersion);
	}

	
	if (hasLayerProperty("VK_LAYER_VALVE_steam_overlay", instanceLayerProperties)) {
		m_validationLayersEnabled.push_back("VK_LAYER_VALVE_steam_overlay");
	}
#ifdef _DEBUG
	if (hasLayerProperty("VK_LAYER_LUNARG_standard_validation", instanceLayerProperties)) {
		m_validationLayersEnabled.push_back("VK_LAYER_LUNARG_standard_validation");
	}
	else {
		LOG_F(ERROR, "Unable to find layer %s in instanceLayerProperties", "VK_LAYER_LUNARG_standard_validation");
	}

	if (hasLayerProperty("VK_LAYER_KHRONOS_validation", instanceLayerProperties)) {
		m_validationLayersEnabled.push_back("VK_LAYER_KHRONOS_validation");
	}
	else {
		LOG_F(ERROR, "Unable to find layer %s in instanceLayerProperties", "VK_LAYER_KHRONOS_validation");
	}

	if (hasExtensionProperty(VK_EXT_DEBUG_REPORT_EXTENSION_NAME, instanceExtensionProperties)) {
		m_extensionsEnabled.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	}
	else {
		LOG_F(WARNING, "Unable to find extension %s in instanceExtensionProperties", VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	}
#endif

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledLayerCount = static_cast<uint32_t>(m_validationLayersEnabled.size());
	createInfo.ppEnabledLayerNames = m_validationLayersEnabled.data();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(m_extensionsEnabled.size());
	createInfo.ppEnabledExtensionNames = m_extensionsEnabled.data();

	if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS) {
		ABORT_F("Failed to create VkInstance");
	}
}

void VulkanDevice::destroyDevice()
{
	vkDestroyInstance(m_instance, nullptr);
}
