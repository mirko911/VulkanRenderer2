#pragma once

#include <vulkan/vulkan.hpp>
#include <loguru.hpp>

// Setup and functions for the VK_EXT_debug_marker_extension
// Extension spec can be found at https://github.com/KhronosGroup/Vulkan-Docs/blob/1.0-VK_EXT_debug_marker/doc/specs/vulkan/appendices/VK_EXT_debug_marker.txt
// Note that the extension will only be present if run from an offline debugging application
namespace DebugMarker
{
	inline bool active = false;
	inline bool extensionPresent = false;

	inline PFN_vkDebugMarkerSetObjectTagEXT vkDebugMarkerSetObjectTag = VK_NULL_HANDLE;
	inline PFN_vkDebugMarkerSetObjectNameEXT vkDebugMarkerSetObjectName = VK_NULL_HANDLE;
	inline PFN_vkCmdDebugMarkerBeginEXT vkCmdDebugMarkerBegin = VK_NULL_HANDLE;
	inline PFN_vkCmdDebugMarkerEndEXT vkCmdDebugMarkerEnd = VK_NULL_HANDLE;
	inline PFN_vkCmdDebugMarkerInsertEXT vkCmdDebugMarkerInsert = VK_NULL_HANDLE;

	// Get function pointers for the debug report extensions from the device
	inline void setup(VkDevice device, VkPhysicalDevice physicalDevice)
	{
		// Check if the debug marker extension is present (which is the case if run from a graphics debugger)
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, extensions.data());
		for (auto extension : extensions) {
			if (strcmp(extension.extensionName, VK_EXT_DEBUG_MARKER_EXTENSION_NAME) == 0) {
				extensionPresent = true;
				break;
			}
		}

		if (extensionPresent) {
			// The debug marker extension is not part of the core, so function pointers need to be loaded manually
			vkDebugMarkerSetObjectTag = (PFN_vkDebugMarkerSetObjectTagEXT)vkGetDeviceProcAddr(device, "vkDebugMarkerSetObjectTagEXT");
			vkDebugMarkerSetObjectName = (PFN_vkDebugMarkerSetObjectNameEXT)vkGetDeviceProcAddr(device, "vkDebugMarkerSetObjectNameEXT");
			vkCmdDebugMarkerBegin = (PFN_vkCmdDebugMarkerBeginEXT)vkGetDeviceProcAddr(device, "vkCmdDebugMarkerBeginEXT");
			vkCmdDebugMarkerEnd = (PFN_vkCmdDebugMarkerEndEXT)vkGetDeviceProcAddr(device, "vkCmdDebugMarkerEndEXT");
			vkCmdDebugMarkerInsert = (PFN_vkCmdDebugMarkerInsertEXT)vkGetDeviceProcAddr(device, "vkCmdDebugMarkerInsertEXT");
			// Set flag if at least one function pointer is present
			active = (vkDebugMarkerSetObjectName != VK_NULL_HANDLE);

			LOG_F(INFO, "%s extension present and %s", VK_EXT_DEBUG_MARKER_EXTENSION_NAME, (active) ? "active" : "inactive");
		}
		else {
			LOG_F(WARNING, "Warning %s  not present, debug markers are disabled.", VK_EXT_DEBUG_MARKER_EXTENSION_NAME);
		}
	}

	// Sets the debug name of an object
	// All Objects in Vulkan are represented by their 64-bit handles which are passed into this function
	// along with the object type
	inline void setObjectName(VkDevice device, uint64_t object, VkDebugReportObjectTypeEXT objectType, const char* name)
	{
		// Check for valid function pointer (may not be present if not running in a debugging application)
		if (active)
		{
			VkDebugMarkerObjectNameInfoEXT nameInfo = {};
			nameInfo.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT;
			nameInfo.objectType = objectType;
			nameInfo.object = object;
			nameInfo.pObjectName = name;
			vkDebugMarkerSetObjectName(device, &nameInfo);
		}
	}

	// Set the tag for an object
	inline void setObjectTag(VkDevice device, uint64_t object, VkDebugReportObjectTypeEXT objectType, uint64_t name, size_t tagSize, const void* tag)
	{
		//// Check for valid function pointer (may not be present if not running in a debugging application)
		//if (active)
		//{
		//	VkDebugMarkerObjectTagInfoEXT tagInfo = {};
		//	tagInfo.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_TAG_INFO_EXT;
		//	tagInfo.objectType = objectType;
		//	tagInfo.object = object;
		//	tagInfo.tagName = name;
		//	tagInfo.tagSize = tagSize;
		//	tagInfo.pTag = tag;
		//	vkDebugMarkerSetObjectTag(device, &tagInfo);
		//}
	}

	// Start a new debug marker region
	inline void beginRegion(VkCommandBuffer cmdbuffer, const char* pMarkerName, glm::vec4 color)
	{
		// Check for valid function pointer (may not be present if not running in a debugging application)
		if (active)
		{
			VkDebugMarkerMarkerInfoEXT markerInfo = {};
			markerInfo.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT;
			memcpy(markerInfo.color, &color[0], sizeof(float) * 4);
			markerInfo.pMarkerName = pMarkerName;
			vkCmdDebugMarkerBegin(cmdbuffer, &markerInfo);
		}
	}

	// Insert a new debug marker into the command buffer
	inline void insert(VkCommandBuffer cmdbuffer, std::string markerName, glm::vec4 color)
	{
		// Check for valid function pointer (may not be present if not running in a debugging application)
		if (active)
		{
			VkDebugMarkerMarkerInfoEXT markerInfo = {};
			markerInfo.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT;
			memcpy(markerInfo.color, &color[0], sizeof(float) * 4);
			markerInfo.pMarkerName = markerName.c_str();
			vkCmdDebugMarkerInsert(cmdbuffer, &markerInfo);
		}
	}

	// End the current debug marker region
	inline void endRegion(VkCommandBuffer cmdBuffer)
	{
		// Check for valid function (may not be present if not runnin in a debugging application)
		if (vkCmdDebugMarkerEnd)
		{
			vkCmdDebugMarkerEnd(cmdBuffer);
		}
	}
};
