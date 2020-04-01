#pragma once
#include <string>
#include <fstream>

#include <loguru.hpp>
#include <vulkan/vulkan.hpp>

class Shader
{
private:
	VkDevice m_device;
	std::vector<VkPipelineShaderStageCreateInfo> m_shaderStageCreateInfos;

	std::vector<char> readBinary(const std::string& filename);
	VkShaderModule createShaderModule(const std::vector<char>& shaderBinary);

public:
	void Init(const VkDevice& device);
	void Destroy();
	void addShaderStage(const VkShaderStageFlagBits shaderStage, const std::string& filename);
	std::vector<VkPipelineShaderStageCreateInfo>& getShaderStages();
};

