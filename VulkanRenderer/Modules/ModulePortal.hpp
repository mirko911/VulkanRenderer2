#pragma once

#include <vector>

#include <vulkan/vulkan.hpp>
#include <loguru.hpp>

#include "../defintions.hpp"

#include "ModuleBase.hpp"

class ModulePortal : public ModuleBase {
	std::string m_debugName = "Generic Portal";
private:
public:
	//void update(const float ftimeDelta, GameRoot& gameRoot);
	void init(VulkanDevice& device);
};