#pragma once

#include <vector>

#include <vulkan/vulkan.hpp>
#include <loguru.hpp>

#include "../defintions.hpp"

#include "ModuleBase.hpp"

class ModuleMaterial : public ModuleBase {
	std::string m_debugName = "Generic Portal";
	MaterialBlock m_material;
private:
public:
	//void update(const float ftimeDelta, GameRoot& gameRoot);
	void init(VulkanDevice& device);

	void setAmbientColor(const Vec4 color);
	void setDiffuseColor(const Vec4 color);
	void setSpecularColor(const Vec4 color);
	void setTextureID(const uint32_t ID);
	void setNormalMapID(const uint32_t ID);
	void setAmbientStrength(const float strength);
	void setSpecularStrength(const float strength);

	MaterialBlock& getMaterialBlock();
};