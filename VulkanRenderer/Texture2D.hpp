#pragma once

#include <string>

#include "defintions.hpp"
#include "Buffer.hpp"

#include "CommandBuffer.hpp"
#include "Texture.hpp"
#include "Sampler.hpp"


class Texture2D : public Texture
{
private:
	int32_t m_moduleID = ENTITY_NOT_FOUND;
	std::string m_debugName = "Generic 2D Texture";
	std::string m_fileName;
	Sampler m_sampler;
	const VkFormat m_format = VK_FORMAT_R8G8B8A8_UNORM;
public:
	Texture2D(const std::string& filename);

	void setModuleID(const int32_t ID);
	int32_t getModuleID() const;

	void setDebugName(const std::string& name);
	std::string getDebugName() const;

	void Init(const VkDevice& device, const VkPhysicalDevice& gpu, const Queue& queueGraphics) override;

	void createTexture(CommandBuffer& commandBuffer);
	void createSampler();
	Sampler& getSampler();
	VkDescriptorImageInfo getDescriptorImageInfo();
};

