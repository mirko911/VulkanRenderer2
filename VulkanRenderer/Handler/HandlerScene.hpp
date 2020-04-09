#pragma once

#include <utility>

#include "HandlerBase.hpp"

#include "../Scene.hpp"

class HandlerScene : public HandlerBase{
private:
	std::unordered_map<int32_t, std::unique_ptr<Scene>> m_entities;
public:
	//HandlerTransformation();

	template <typename... Args>
	ModuleInfo<Scene> create(Args&& ... args) {
		const int32_t ID = getNextModuleID();

		m_entities[ID] = std::make_unique<Scene>(std::forward<Args>(args)...);
		m_entities[ID]->setModuleID(ID);

		return { ID, reinterpret_cast<Scene*>(m_entities[ID].get()) };
	}

	Scene* get(const int32_t ID ) {
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

	std::unordered_map<int32_t, std::unique_ptr<Scene>>& getAll();


	//virtual void init(VulkanDevice& device);
	//virtual void update(const float fTimeDelta);
};