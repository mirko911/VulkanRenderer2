#pragma once

#include <loguru.hpp>
#include <vulkan/vulkan.hpp>

#include "VulkanDevice.hpp"
#include "Shader.hpp"
#include "RenderPass.hpp"
#include "Pipeline.hpp"
#include "Swapchain.hpp"
#include "Texture.hpp"
#include "CommandBuffer.hpp"
#include "CommandPool.hpp"
#include "Descriptor.hpp"
#include "DescriptorPool.hpp"
#include "Buffer.hpp"

#include "GameRoot.hpp"

constexpr int MAX_FRAMES_IN_FLIGHT = 3;

class Renderer
{
private:
	RenderPass m_renderpass;
	Pipeline m_pipeline;
	Shader m_shader;
	VulkanDevice m_vulkanDevice;
	Swapchain m_swapchain;

	CommandPool m_commandPool;
	std::vector<CommandBuffer> m_commandBuffers;

	std::vector<VkSemaphore> m_imageAvailableSemaphore;
	std::vector<VkSemaphore> m_renderFinishedSemaphore;
	std::vector<VkFence> m_inFlightFences;
	std::vector<VkFence> m_imagesInFlight;

	size_t m_currentFrame = 0;

	struct {
		Buffer mainUBO;
		Buffer mainUBODyn;
	} m_buffers;

	//Dynamic Alignment Size for DynUBO
	VkDeviceSize m_dynamicAlignment;

public:
	void Init(VulkanDevice& device, GameRoot& gameRoot);
	void Render(GameRoot& gameRoot);
	void updateUniformBuffer(GameRoot& gameRoot);
	void Destroy();
};

