#pragma once

#include <loguru.hpp>
#include <vulkan/vulkan.hpp>

struct QueueFamilyIndices {
	uint32_t graphicsFamily = VK_QUEUE_FAMILY_IGNORED;
	uint32_t presentFamily = VK_QUEUE_FAMILY_IGNORED;
	uint32_t computeFamily = VK_QUEUE_FAMILY_IGNORED;

	bool isComplete() {
		return (
			graphicsFamily != VK_QUEUE_FAMILY_IGNORED &&
			presentFamily != VK_QUEUE_FAMILY_IGNORED);
	}
};