#pragma once

#include <utility>

#include "HandlerBase.hpp"

#include "../SceneNode.hpp"

class HandlerSceneNode : public HandlerBase{
private:
	std::unordered_map<int32_t, std::unique_ptr<SceneNode>> m_entities;
public:
	//HandlerTransformation();

	template <typename... Args>
	ModuleInfo<SceneNode> create(Args&& ... args) {
		const int32_t ID = getNextModuleID();

		m_entities[ID] = std::make_unique<SceneNode>(std::forward<Args>(args)...);
		m_entities[ID]->setModuleID(ID);

		return { ID, reinterpret_cast<SceneNode*>(m_entities[ID].get()) };
	}

	SceneNode* get(const int32_t ID ) {
		if (!has(ID)) {
			LOG_F(ERROR, "Entity (ID %i) doesn't exist in %s", ID, getDebugName().c_str());
		}

		return m_entities[ID].get();
	}


	bool has(const int32_t ID) {
		return (m_entities.find(ID) != m_entities.end());
	}

	void remove(const int32_t ID) {
		m_entities.erase(ID);
	}

	std::unordered_map<int32_t, std::unique_ptr<SceneNode>>& getAll();


	//virtual void init(VulkanDevice& device);
	void update(const float fTimeDelta, GameRoot& gameRoot);

	void clear();
};