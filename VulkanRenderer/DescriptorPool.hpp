#pragma once

#include <loguru.hpp>
#include <vulkan/vulkan.hpp>

#include "Descriptor.hpp"


class DescriptorPool
{
private:
	VkDevice m_device;
	VkPhysicalDevice m_gpu;
	VkDescriptorPool m_descriptorPool;
public:
	void Init(const VkDevice& device, const VkPhysicalDevice& gpu);
	void create(std::vector<Descriptor>& descriptors);
	VkDescriptorPool& getDescriptorPool();
	void allocateDescriptorSets(std::vector<Descriptor>& descriptors);
};

