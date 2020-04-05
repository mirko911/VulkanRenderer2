#pragma once

#include <loguru.hpp>
#include <stdint.h>
#include "../VulkanDevice.hpp"

class ModuleBase {
private:
	uint32_t m_moduleID;
public:
	ModuleBase() = default;
	void init(VulkanDevice& device);
	void update(const float ftimeDelta);
	void setModuleID(const uint32_t moduleID);
	uint32_t getModuleID() const;
};