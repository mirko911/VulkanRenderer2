#pragma once

#include <loguru.hpp>
#include <vulkan/vulkan.hpp>

class Sampler
{
private:
	VkDevice m_device;
	VkPhysicalDevice m_gpu;
	VkSampler m_sampler;
public:
	void Init(const VkDevice& device, const VkPhysicalDevice& gpu);
	void create();
	VkSampler& getSampler();
};

