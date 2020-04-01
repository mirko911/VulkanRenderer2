#pragma once

#include <loguru.hpp>
#include <vulkan/vulkan.hpp>

class RenderPass
{
private:
	VkRenderPass m_renderpass;
public:
	VkRenderPass& get();
	VkExtent2D getExtend();
	uint32_t getWidth();
	uint32_t getHeight();
};

