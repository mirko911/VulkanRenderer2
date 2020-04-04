#pragma once
#include <vector>
#include <unordered_map>

#include <loguru.hpp>
#include <vulkan/vulkan.hpp>

#include "Buffer.hpp"
class Descriptor
{
private:
	VkDevice m_device;
	VkPhysicalDevice m_gpu;
	std::vector<VkDescriptorSetLayoutBinding> m_layoutBinding;
	std::unordered_map<VkDescriptorType, uint32_t> m_typeCounter;
	VkDescriptorSetLayout m_descriptorLayout;
	VkDescriptorSet m_descriptorSet;
public:
	void Init(const VkDevice& device);
	void addLayoutBinding(const uint32_t binding, const VkDescriptorType type, const VkShaderStageFlags flag, const uint32_t descriptorCount = 1);
	std::unordered_map<VkDescriptorType, uint32_t>& getTypeCounter();
	void createDescriptorSetLayout();
	VkDescriptorSet& getDescriptorSet();
	void setDescriptorSet(const VkDescriptorSet descriptorSet);
	VkDescriptorSetLayout& getDescriptorSetLayout();
	void writeSet(const uint32_t binding, const VkDescriptorType type, Buffer& buffer);
};

