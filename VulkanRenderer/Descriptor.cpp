#include "Descriptor.hpp"

void Descriptor::Init(const VkDevice& device)
{
	m_device = device;
}

void Descriptor::addLayoutBinding(const uint32_t binding, const VkDescriptorType type, const VkShaderStageFlags flag, const uint32_t descriptorCount)
{
	VkDescriptorSetLayoutBinding layoutBinding = {};
	layoutBinding.binding = binding;
	layoutBinding.descriptorType = type;
	layoutBinding.descriptorCount = descriptorCount;
	layoutBinding.stageFlags = flag;
	layoutBinding.pImmutableSamplers = nullptr; // Optional

	if (m_typeCounter.find(type) == m_typeCounter.end()) {
		m_typeCounter[type] = 0;
	}

	m_typeCounter[type]++;

	m_layoutBinding.emplace_back(layoutBinding);
}

std::unordered_map<VkDescriptorType, uint32_t>& Descriptor::getTypeCounter()
{
	return m_typeCounter;
}

void Descriptor::createDescriptorSetLayout()
{
		VkDescriptorSetLayoutCreateInfo layoutInfo = {};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = static_cast<uint32_t>(m_layoutBinding.size());
		layoutInfo.pBindings = m_layoutBinding.data();

		if (vkCreateDescriptorSetLayout(m_device, &layoutInfo, nullptr, &m_descriptorLayout) != VK_SUCCESS) {
			ABORT_F("failed to create descriptor set layout!");
		}
}

VkDescriptorSet& Descriptor::getDescriptorSet()
{
	return m_descriptorSet;
}

void Descriptor::setDescriptorSet(const VkDescriptorSet descriptorSet)
{
	m_descriptorSet = descriptorSet;
}

VkDescriptorSetLayout& Descriptor::getDescriptorSetLayout()
{
	return m_descriptorLayout;
}

void Descriptor::writeSet(const uint32_t binding, const VkDescriptorType type, Buffer& buffer)
{
	VkWriteDescriptorSet writeDescriptorSet = {};
	writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	writeDescriptorSet.dstSet = m_descriptorSet;
	writeDescriptorSet.dstBinding = binding;
	writeDescriptorSet.dstArrayElement = 0;
	writeDescriptorSet.descriptorType = type;
	writeDescriptorSet.descriptorCount = 1;
	writeDescriptorSet.pBufferInfo = &buffer.descriptor;

	vkUpdateDescriptorSets(m_device, static_cast<uint32_t>(1), &writeDescriptorSet, 0, nullptr);
}

void Descriptor::writeSet(const uint32_t binding, const VkDescriptorType type, const std::vector<VkDescriptorImageInfo>& descriptorImageInfo)
{
	VkWriteDescriptorSet writeDescriptorSet = {};
	writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	writeDescriptorSet.dstSet = m_descriptorSet;
	writeDescriptorSet.dstBinding = binding;
	writeDescriptorSet.dstArrayElement = 0;
	writeDescriptorSet.descriptorType = type;
	writeDescriptorSet.descriptorCount = static_cast<uint32_t>(descriptorImageInfo.size());
	writeDescriptorSet.pImageInfo = descriptorImageInfo.data();

	vkUpdateDescriptorSets(m_device, static_cast<uint32_t>(1), &writeDescriptorSet, 0, nullptr);
}
