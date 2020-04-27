#pragma once

#include <utility>

#include "HandlerBase.hpp"

#include "../modules/ModuleBase.hpp"
#include "../modules/ModulePortal.hpp"

#include "../GameObject.hpp"


class HandlerPortal : public HandlerBase{
private:
	std::unordered_map<int32_t, std::unique_ptr<ModulePortal>> m_entities;
public:
	//HandlerTransformation();

	template <typename... Args>
	ModuleInfo<ModulePortal> create(Args&& ... args) {
		const int32_t ID = getNextModuleID();

		m_entities[ID] = std::make_unique<ModulePortal>(std::forward<Args>(args)...);
		m_entities[ID]->setModuleID(ID);

		return { ID, reinterpret_cast<ModulePortal*>(m_entities[ID].get()) };
	}

	ModulePortal* get(const int32_t ID ) {
		if (!has(ID)) {
			LOG_F(ERROR, "Entity (ID %i) doesn't exist in %s", ID, getDebugName().c_str());
		}

		return m_entities[ID].get();
	}

	ModulePortal* get(GameObject* gameobject) {
		if (!gameobject->hasModule<ModulePortal>()) {
			LOG_F(ERROR, "Entity doesn't have module %s", gameobject->getDebugName().c_str());
		}
		const int32_t ID = gameobject->getModule<ModulePortal>();
		return m_entities[ID].get();
	}



	bool has(const int32_t ID) {
		return (m_entities.find(ID) != m_entities.end());
	}

	void remove(const int32_t ID) {
		m_entities.erase(ID);
	}

	std::unordered_map<int32_t, std::unique_ptr<ModulePortal>>& getAll();


	void init(VulkanDevice& device);
	void update(const float fTimeDelta, GameRoot& gameRoot);

	void clear();
};
