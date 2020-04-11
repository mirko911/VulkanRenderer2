#pragma once
#include <string>
#include <array>

#include "Texture.hpp"
#include "Sampler.hpp"
#include "Buffer.hpp"

class TextureCubemap : public Texture
{
private:
	int32_t m_moduleID = ENTITY_NOT_FOUND;
	std::string m_debugName = "Generic Cubemap";
	std::string m_fileName;
	std::string m_fileExtension;
	Sampler m_sampler;
	const std::array<const std::string, 6> m_names = { "front", "back", "top", "bottom" , "left", "right" };
	VkFormat m_format = VK_FORMAT_R8G8B8A8_UNORM;
public:
	void setModuleID(const int32_t ID);
	int32_t getModuleID() const;

	void setDebugName(const std::string& name);
	std::string getDebugName() const;

	TextureCubemap(const std::string& filename, const std::string& fileExtension);
	void Init(const VkDevice& device, const VkPhysicalDevice& gpu, const Queue& ququeGraphics);
	void createTexture(CommandBuffer& copyCMDBuffer);
	void createSampler();
	Sampler& getSampler();
	VkDescriptorImageInfo getDescriptorImageInfo();
};

