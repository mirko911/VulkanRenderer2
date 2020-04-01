#pragma once

#include <loguru.hpp>
#include <vulkan/vulkan.hpp>

#include "VulkanDevice.hpp"
#include "Shader.hpp"
#include "RenderPass.hpp"
#include "Pipeline.hpp"


class Renderer
{
private:
	RenderPass m_renderpass;
	Pipeline m_pipeline;
	Shader m_shader;
	VulkanDevice m_vulkanDevice;
public:
	void Init(VulkanDevice& device);
	void Destroy();
};

