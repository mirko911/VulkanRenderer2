#include "HandlerTexture.hpp"


std::unordered_map<int32_t, std::unique_ptr<Texture2D>>& HandlerTexture::getAll2D()
{
	return m_textures2D;
}

std::unordered_map<int32_t, std::unique_ptr<TextureCubemap>>& HandlerTexture::getAllCubemap()
{
	return m_texturesCubemap;
}

void HandlerTexture::init(VulkanDevice& device)
{
	CommandBuffer copyCMDBuffer = device.getCommandPool().allocateCommandBuffer();

	for (auto& texture : m_textures2D) {
		texture.second->Init(device.getDevice(), device.getGPU(), device.getGraphicsQueue());
		texture.second->createTexture(copyCMDBuffer);
		texture.second->createSampler();
	}
	for (auto& texture : m_texturesCubemap) {
		texture.second->Init(device.getDevice(), device.getGPU(), device.getGraphicsQueue());
		texture.second->createTexture(copyCMDBuffer);
		texture.second->createSampler();
	}
}
