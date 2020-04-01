#include "Renderer.hpp"

void Renderer::Init(VulkanDevice& device)
{
	m_shader.Init(device.getDevice());
	m_shader.addShaderStage(VK_SHADER_STAGE_VERTEX_BIT, "shaders/main.vert.spv");
	m_shader.addShaderStage(VK_SHADER_STAGE_VERTEX_BIT, "shaders/main.frag.spv");
}
