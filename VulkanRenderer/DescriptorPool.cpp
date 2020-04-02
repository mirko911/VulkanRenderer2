#include "DescriptorPool.hpp"

void DescriptorPool::Init(const VkDevice& device, const VkPhysicalDevice& gpu)
{
	m_device = device;
	m_gpu = gpu;
}

void DescriptorPool::create(std::vector<Descriptor>& descriptors)
{
	std::unordered_map<VkDescriptorType, uint32_t> m_typeSums;
	for (Descriptor& descriptor : descriptors) {
		for (const auto& typeCounter : descriptor.getTypeCounter()) {
			if (m_typeSums.find(typeCounter.first) == m_typeSums.end()) {
				m_typeSums[typeCounter.first] = 0;
			}
			
			m_typeSums[typeCounter.first] += typeCounter.second;
		}
	}

	std::vector<VkDescriptorPoolSize> poolSizes;

	for (const auto& typeSum : m_typeSums) {
		VkDescriptorPoolSize size = {};
		size.type = typeSum.first;
		size.descriptorCount = typeSum.second;
		poolSizes.push_back(size);
	}

	VkDescriptorPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
	poolInfo.pPoolSizes = poolSizes.data();
	poolInfo.maxSets = static_cast<uint32_t>(descriptors.size());

	if (vkCreateDescriptorPool(m_device, &poolInfo, nullptr, &m_descriptorPool) != VK_SUCCESS) {
		ABORT_F("failed to create descriptor pool!");
	}
}

VkDescriptorPool& DescriptorPool::getDescriptorPool()
{
	return m_descriptorPool;
}

void DescriptorPool::allocateDescriptorSets(std::vector<Descriptor>& descriptors)
{
	std::vector<VkDescriptorSetLayout> m_layouts;
	std::vector<VkDescriptorSet> descriptorSets;

	m_layouts.reserve(descriptors.size());
	descriptorSets.resize(descriptors.size());

	for (Descriptor& descriptor : descriptors) {
		m_layouts.push_back(descriptor.getDescriptorSetLayout());
	}

	VkDescriptorSetAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = m_descriptorPool;
	allocInfo.descriptorSetCount = static_cast<uint32_t>(m_layouts.size());
	allocInfo.pSetLayouts = m_layouts.data();

	VkDescriptorSet set;
	if (vkAllocateDescriptorSets(m_device, &allocInfo, descriptorSets.data()) != VK_SUCCESS) {
		ABORT_F("failed to allocate descriptor sets!");
	}

	for (size_t i = 0; i < descriptors.size(); i++) {
		descriptors[i].setDescriptorSet(descriptorSets[i]);
	}
	
}
