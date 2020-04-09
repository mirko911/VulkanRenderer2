#pragma once

#include <vector>

#include <vulkan/vulkan.hpp>
#include <loguru.hpp>
#include "ModuleBase.hpp"
#include "../Buffer.hpp"
#include "../CommandBuffer.hpp"
class ModuleTransformation : public ModuleBase {
	std::string m_debugName = "Generic Transformation";
public:
	void update(const float ftimeDelta);
	void init(VulkanDevice& device);

};