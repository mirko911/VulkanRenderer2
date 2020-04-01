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

QueueFamilyIndices VulkanDevice::getQueueFamilyProperties()
{
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(m_gpu, &queueFamilyCount, nullptr);
	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(m_gpu, &queueFamilyCount, queueFamilies.data());

	QueueFamilyIndices queueFamilyIndices;

	uint32_t i = 0;
	//for (const VkQueueFamilyProperties& queueFamily : queueFamilies) {
	//	if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
	//		queueFamilyIndices.graphicsFamily = i;
	//	}

	//	VkBool32 hasPresentionQueue = false;
	//	vkGetPhysicalDeviceSurfaceSupportKHR(m_gpu, static_cast<uint32_t>(i), m_surface, &hasPresentionQueue);

	//	if (hasPresentionQueue) {
	//		queueFamilyIndices.presentFamily = i;
	//	}

	//	if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT && i != queueFamilyIndices.presentFamily) {
	//		queueFamilyIndices.computeFamily = i;
	//	}


	//	if (queueFamilyIndices.isComplete()) {
	//		break;
	//	}

	//	i++;
	//}

	for (size_t i = 0; i < queueFamilies.size(); i++)
	{
		VkBool32 hasPresentionQueue = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(m_gpu, static_cast<uint32_t>(i), m_surface, &hasPresentionQueue);




		if (queueFamilies[i].queueCount > 0 && hasPresentionQueue)
		{
			queueFamilyIndices.presentFamily = static_cast<uint32_t>(i); 	// presentation queue
		}
		if (queueFamilies[i].queueCount > 0 && queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			queueFamilyIndices.graphicsFamily = static_cast<uint32_t>(i); 	// graphics queue - if possible, use seperate queues for compute and graphic transfer
		}
		if (queueFamilies[i].queueCount > 0 && i != queueFamilyIndices.presentFamily &&
			queueFamilies[i].queueFlags & VK_QUEUE_COMPUTE_BIT)
		{
			queueFamilyIndices.computeFamily = static_cast<uint32_t>(i); 	// compute queue
		}
	}

	if (queueFamilyIndices.presentFamily == VK_QUEUE_FAMILY_IGNORED) {
		ABORT_F("Required presentationQueueIndex not found");
	}
	if (queueFamilyIndices.computeFamily == VK_QUEUE_FAMILY_IGNORED) {
		//	// The preference is a sepearte compute queue as this will be faster, though if not found, use the graphics queue for compute shaders
		queueFamilyIndices.computeFamily = queueFamilyIndices.graphicsFamily;
	}
	return queueFamilyIndices;
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


	/*LOG_F(INFO, "Available instance extensions:");
	for (const VkExtensionProperties& extensionProperties : instanceExtensionProperties) {
		LOG_F(INFO, "\t %s (%i)", extensionProperties.extensionName, extensionProperties.specVersion);
	}*/


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

void VulkanDevice::createSurface(GLFWwindow* window)
{
	if (m_instance == VK_NULL_HANDLE) {
		ABORT_F("vkInstance must be created before calling createSurface");
	}

	if (glfwCreateWindowSurface(m_instance, window, nullptr, &m_surface) != VK_SUCCESS) {
		ABORT_F("Failed to create vkSurface");
	}
}

void VulkanDevice::createDevice()
{
	if (m_instance == VK_NULL_HANDLE) {
		ABORT_F("vkInstance must be created before calling createDevice");
	}

	//Vulkan Tutorial : pickPhysicalDevice
	uint32_t availableGPUCount = 0;
	vkEnumeratePhysicalDevices(m_instance, &availableGPUCount, nullptr);
	std::vector<VkPhysicalDevice> availableGPUs(availableGPUCount);
	vkEnumeratePhysicalDevices(m_instance, &availableGPUCount, availableGPUs.data());

	if (availableGPUCount == 0) {
		ABORT_F("Failed to find GPUs with Vulkan Support");
	}


	LOG_F(INFO, "Available GPUs:");
	for (const VkPhysicalDevice& gpu : availableGPUs) {
		VkPhysicalDeviceProperties props;
		vkGetPhysicalDeviceProperties(gpu, &props);

		if (m_gpu  == VK_NULL_HANDLE) {
			m_gpu = gpu;
			LOG_F(INFO, "\t%s (active)", props.deviceName);
		}
		else {
			LOG_F(INFO, "\t%s", props.deviceName);
		}
	}

	QueueFamilyIndices familyIndices = getQueueFamilyProperties();
	LOG_F(INFO, "Available QueueFamilys:");
	LOG_F(INFO, "\tPresent: %i",familyIndices.presentFamily);
	LOG_F(INFO, "\tGraphics:%i",familyIndices.graphicsFamily);
	LOG_F(INFO, "\tCompute: %i",familyIndices.computeFamily);


	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::vector<uint32_t> uniqueQueueFamilies = { familyIndices.graphicsFamily, familyIndices.presentFamily,};

	float queuePriority = 1.0f;
	for (int queueFamily : uniqueQueueFamilies) {
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	VkPhysicalDeviceFeatures requiredFeatures = {};
	VkPhysicalDeviceFeatures availableFeatures;
	vkGetPhysicalDeviceFeatures(m_gpu, &availableFeatures);

	if (availableFeatures.textureCompressionETC2) {
		requiredFeatures.textureCompressionETC2 = VK_TRUE;
	}
	if (availableFeatures.textureCompressionBC) {
		requiredFeatures.textureCompressionBC = VK_TRUE;
	}
	if (availableFeatures.samplerAnisotropy) {
		requiredFeatures.samplerAnisotropy = VK_TRUE;
	}
	if (availableFeatures.tessellationShader) {
		requiredFeatures.tessellationShader = VK_TRUE;
	}
	if (availableFeatures.geometryShader) {
		requiredFeatures.geometryShader = VK_TRUE;
	}
	if (availableFeatures.shaderStorageImageExtendedFormats) {
		requiredFeatures.shaderStorageImageExtendedFormats = VK_TRUE;
	}


	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(m_gpu, nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> deviceExtesionProperties(extensionCount);
	vkEnumerateDeviceExtensionProperties(m_gpu, nullptr, &extensionCount, deviceExtesionProperties.data());
	/*LOG_F(INFO, "Available device extensions:");
	for (const VkExtensionProperties& extensionProperties : deviceExtesionProperties) {
		LOG_F(INFO, "\t %s (%i)", extensionProperties.extensionName, extensionProperties.specVersion);
	}*/

	std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
	if (!hasExtensionProperty(VK_KHR_SWAPCHAIN_EXTENSION_NAME, deviceExtesionProperties)) {
		ABORT_F("Unable to find extension %s in deviceExtesionProperties", VK_KHR_SWAPCHAIN_EXTENSION_NAME);
	}

	if (hasExtensionProperty(VK_EXT_DEBUG_MARKER_EXTENSION_NAME, deviceExtesionProperties)) {
		deviceExtensions.push_back(VK_EXT_DEBUG_MARKER_EXTENSION_NAME);
	}

	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pEnabledFeatures = &requiredFeatures;
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.enabledLayerCount = static_cast<uint32_t>(m_validationLayersEnabled.size());
	createInfo.ppEnabledLayerNames = m_validationLayersEnabled.data();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = deviceExtensions.data();

	if (vkCreateDevice(m_gpu, &createInfo, nullptr, &m_device) != VK_SUCCESS) {
		ABORT_F("Failed to create logical device");
	}

	//Setup Debug Marker here

	m_queueGraphics.Init(m_device, familyIndices.graphicsFamily);
	m_queuePresent.Init(m_device, familyIndices.presentFamily);
}

void VulkanDevice::destroyDevice()
{
	vkDestroyDevice(m_device, nullptr);
	vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
	vkDestroyInstance(m_instance, nullptr);
}

VkInstance& VulkanDevice::getInstance()
{
	return m_instance;
}

VkDevice& VulkanDevice::getDevice()
{
	return m_device;
}

VkPhysicalDevice& VulkanDevice::getGPU()
{
	return m_gpu;
}

VkSurfaceKHR& VulkanDevice::getSurface()
{
	return m_surface;
}

Queue& VulkanDevice::getGraphicsQueue()
{
	return m_queueGraphics;
}

Queue& VulkanDevice::getPresentQueue()
{
	return m_queuePresent;
}
