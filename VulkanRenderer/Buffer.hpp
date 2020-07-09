#pragma once
#include <loguru.hpp>
#include <vulkan/vulkan.hpp>

#include "VulkanDevice.hpp"
struct Buffer
{
	VkDevice device;
	VkBuffer buffer = VK_NULL_HANDLE;
	VkDeviceMemory memory = VK_NULL_HANDLE;
	VkDescriptorBufferInfo descriptor;
	VkDeviceSize size = 0;
	VkDeviceSize alignment = 0;
	void* mapped = nullptr;

	/** @brief Usage flags to be filled by external source at buffer creation (to query at some later point) */
	VkBufferUsageFlags usageFlags;
	/** @brief Memory propertys flags to be filled by external source at buffer creation (to query at some later point) */
	VkMemoryPropertyFlags memoryPropertyFlags;

	/**
	* Map a memory range of this buffer. If successful, mapped points to the specified buffer range.
	*
	* @param size (Optional) Size of the memory range to map. Pass VK_WHOLE_SIZE to map the complete buffer range.
	* @param offset (Optional) Byte offset from beginning
	*
	* @return VkResult of the buffer mapping call
	*/
	VkResult map(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0)
	{
		return vkMapMemory(device, memory, offset, size, 0, &mapped);
	}

	/**
	* Unmap a mapped memory range
	*
	* @note Does not return a result as vkUnmapMemory can't fail
	*/
	void unmap()
	{
		if (mapped)
		{
			vkUnmapMemory(device, memory);
			mapped = nullptr;
		}
	}

	/**
	* Attach the allocated memory block to the buffer
	*
	* @param offset (Optional) Byte offset (from the beginning) for the memory region to bind
	*
	* @return VkResult of the bindBufferMemory call
	*/
	VkResult bind(VkDeviceSize offset = 0)
	{
		return vkBindBufferMemory(device, buffer, memory, offset);
	}

	/**
	* Setup the default descriptor for this buffer
	*
	* @param size (Optional) Size of the memory range of the descriptor
	* @param offset (Optional) Byte offset from beginning
	*
	*/
	void setupDescriptor(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0)
	{
		descriptor.offset = offset;
		descriptor.buffer = buffer;
		descriptor.range = size;
	}

	/**
	* Copies the specified data to the mapped buffer
	*
	* @param data Pointer to the data to copy
	* @param size Size of the data to copy in machine units
	*
	*/
	void copyTo(void* data, VkDeviceSize size)
	{
		assert(mapped);
		memcpy(mapped, data, size);
	}

	/**
	* Flush a memory range of the buffer to make it visible to the device
	*
	* @note Only required for non-coherent memory
	*
	* @param size (Optional) Size of the memory range to flush. Pass VK_WHOLE_SIZE to flush the complete buffer range.
	* @param offset (Optional) Byte offset from beginning
	*
	* @return VkResult of the flush call
	*/
	VkResult flush(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0)
	{
		VkMappedMemoryRange mappedRange = {};
		mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		mappedRange.memory = memory;
		mappedRange.offset = offset;
		mappedRange.size = size;
		return vkFlushMappedMemoryRanges(device, 1, &mappedRange);
	}

	/**
	* Invalidate a memory range of the buffer to make it visible to the host
	*
	* @note Only required for non-coherent memory
	*
	* @param size (Optional) Size of the memory range to invalidate. Pass VK_WHOLE_SIZE to invalidate the complete buffer range.
	* @param offset (Optional) Byte offset from beginning
	*
	* @return VkResult of the invalidate call
	*/
	VkResult invalidate(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0)
	{
		VkMappedMemoryRange mappedRange = {};
		mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		mappedRange.memory = memory;
		mappedRange.offset = offset;
		mappedRange.size = size;
		return vkInvalidateMappedMemoryRanges(device, 1, &mappedRange);
	}

	/**
	* Release all Vulkan resources held by this buffer
	*/
	void destroy()
	{
		if (buffer)
		{
			vkDestroyBuffer(device, buffer, nullptr);
		}
		if (memory)
		{
			vkFreeMemory(device, memory, nullptr);
		}
	}

	static VkResult createBuffer(const VkDevice& device, const VkPhysicalDevice& gpu, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, Buffer& buffer, VkDeviceSize size, void* data = nullptr)
	{
		buffer.device = device;

		// Create the buffer handle
		VkBufferCreateInfo bufferCreateInfo{};
		bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferCreateInfo.usage = usageFlags;
		bufferCreateInfo.size = size;

		if (vkCreateBuffer(device, &bufferCreateInfo, nullptr, &buffer.buffer) != VK_SUCCESS) {
			ABORT_F("Failed to create buffer");
		};

		// Create the memory backing up the buffer handle
		VkMemoryRequirements memReqs;
		VkMemoryAllocateInfo memAlloc{};
		memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		vkGetBufferMemoryRequirements(device, buffer.buffer, &memReqs);
		memAlloc.allocationSize = memReqs.size;
		// Find a memory type index that fits the properties of the buffer
		memAlloc.memoryTypeIndex = VulkanDevice::findMemoryType(gpu, memReqs.memoryTypeBits, memoryPropertyFlags);
		if (vkAllocateMemory(device, &memAlloc, nullptr, &buffer.memory) != VK_SUCCESS) {
			ABORT_F("Failed to allocate buffer memory");
		};

		buffer.alignment = memReqs.alignment;
		buffer.size = size;
		buffer.usageFlags = usageFlags;
		buffer.memoryPropertyFlags = memoryPropertyFlags;

		// If a pointer to the buffer data has been passed, map the buffer and copy over the data
		if (data != nullptr)
		{
			if (buffer.map() != VK_SUCCESS) {
				ABORT_F("Failed to map buffer");
			};
			memcpy(buffer.mapped, data, size);
			if ((memoryPropertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) == 0)
				buffer.flush();

			buffer.unmap();
		}

		// Initialize a default descriptor that covers the whole buffer size
		buffer.setupDescriptor();

		// Attach the memory to the buffer object
		return buffer.bind();
	};
};


