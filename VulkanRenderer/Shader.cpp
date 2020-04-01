#include "Shader.hpp"

std::vector<char> Shader::readBinary(const std::string& filename)
{
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open()) {
		ABORT_F("failed to open shader %s", filename.c_str());
	}

	size_t fileSize = static_cast<size_t>(file.tellg());
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();

	return buffer;
}

VkShaderModule Shader::createShaderModule(const std::vector<char>& shaderBinary)
{
	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = shaderBinary.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(shaderBinary.data());

	VkShaderModule shaderModule;
	if (vkCreateShaderModule(m_device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
		ABORT_F("failed to create shader module");
	}
	return shaderModule;
}

void Shader::Init(const VkDevice& device)
{
	m_device = device;
}

void Shader::Destroy()
{
	for (const VkPipelineShaderStageCreateInfo& shaderStage : m_shaderStageCreateInfos) {
		vkDestroyShaderModule(m_device, shaderStage.module, nullptr);
	}
	m_shaderStageCreateInfos.clear();
}

void Shader::addShaderStage(const VkShaderStageFlagBits shaderStage, const std::string& filename)
{
	const std::vector<char> shaderBinary = readBinary(filename);
	const VkShaderModule shaderModule = createShaderModule(shaderBinary);

	VkPipelineShaderStageCreateInfo shaderStageInfo = {};
	shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStageInfo.module = shaderModule;
	shaderStageInfo.pName = "main"; //Shader entry point name
	shaderStageInfo.stage = shaderStage;

	m_shaderStageCreateInfos.push_back(shaderStageInfo);
}

std::vector<VkPipelineShaderStageCreateInfo>& Shader::getShaderStages()
{
	return m_shaderStageCreateInfos;
}
