#pragma once

#include <utility>

#include "HandlerBase.hpp"

#include "../Texture2D.hpp"
#include "../TextureCubemap.hpp"


class HandlerTexture : public HandlerBase{
private:
	std::unordered_map<int32_t, std::unique_ptr<Texture2D>> m_textures2D;
	std::unordered_map<int32_t, std::unique_ptr<TextureCubemap>> m_texturesCubemap;

public:
	//HandlerTransformation();

	template <typename... Args>
	ModuleInfo<Texture2D> create2D(Args&& ... args) {
		const int32_t ID = getNextModuleID();

		m_textures2D[ID] = std::make_unique<Texture2D>(std::forward<Args>(args)...);
		m_textures2D[ID]->setModuleID(ID);

		return { ID, reinterpret_cast<Texture2D*>(m_textures2D[ID].get()) };
	}

	template <typename... Args>
	ModuleInfo<TextureCubemap> createCubemap(Args&& ... args) {
		const int32_t ID = static_cast<int32_t>(m_texturesCubemap.size());

		m_texturesCubemap[ID] = std::make_unique<TextureCubemap>(std::forward<Args>(args)...);
		m_texturesCubemap[ID]->setModuleID(ID);

		return { ID, reinterpret_cast<TextureCubemap*>(m_texturesCubemap[ID].get()) };
	}

	Texture2D* get2D(const int32_t ID ) {
		if (!has2D(ID)) {
			LOG_F(ERROR, "Entity (ID %i) doesn't exist in %s", ID, getDebugName().c_str());
		}

		return m_textures2D[ID].get();
	}

	TextureCubemap* getCubemap(const int32_t ID) {
		if (!hasCubemap(ID)) {
			LOG_F(ERROR, "Entity (ID %i) doesn't exist in %s", ID, getDebugName().c_str());
		}

		return m_texturesCubemap[ID].get();
	}

	bool has2D(const int32_t ID) {
		return (m_textures2D.find(ID) != m_textures2D.end());
	}

	bool hasCubemap(const int32_t ID) {
		return (m_texturesCubemap.find(ID) != m_texturesCubemap.end());
	}

	//std::vector<VkDescriptorImageInfo> getCubemapTextureDescriptorImageInfos();

	std::unordered_map<int32_t, std::unique_ptr<Texture2D>>& getAll2D();
	std::unordered_map<int32_t, std::unique_ptr<TextureCubemap>>& getAllCubemap();


	void init(VulkanDevice& device) override;
	//virtual void update(const float fTimeDelta);
};