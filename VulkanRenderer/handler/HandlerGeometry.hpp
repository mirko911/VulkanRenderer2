#pragma once

#include <utility>

#include "HandlerBase.hpp"

#include "../Modules/ModuleBase.hpp"
#include "../Modules/ModuleGeometry.hpp"

#include "../GameObject.hpp"

class HandlerGeometry : public HandlerBase{
private:
	std::unordered_map<int32_t, std::unique_ptr<ModuleGeometry>> m_entities;
public:
	HandlerGeometry();

	template <typename T, typename... Args>
	ModuleInfo<T> create(Args&& ... args) {
		const int32_t ID = getNextModuleID();

		m_entities[ID] = std::make_unique<T>(std::forward<Args>(args)...);
		m_entities[ID]->setModuleID(ID);

		return { ID, reinterpret_cast<T*>(m_entities[ID].get()) };
	}

	template <typename T>
	T* get(const int32_t ID ) {
		if (!has(ID)) {
			LOG_F(ERROR, "Entity (ID %i) doesn't exist in %s", ID, getDebugName().c_str());
		}

		return reinterpret_cast<T*>(m_entities[ID].get());
	}

	template <typename T>
	T* get(GameObject* gameobject) {
		if (!gameobject->hasModule<T>()) {
			LOG_F(ERROR, "Entity doesn't have module %s", gameobject->getDebugName().c_str());
		}
		const int32_t ID = gameobject->getModule<T>();
		return m_entities[ID].get();
	}


	bool has(const int32_t ID) {
		return (m_entities.find(ID) != m_entities.end());
	}

	void remove(const int32_t ID) {
		m_entities.erase(ID);
	}

	std::unordered_map<int32_t, std::unique_ptr<ModuleGeometry>>& getAll();


	void init(VulkanDevice& device) override;
	//virtual void update(const float fTimeDelta);
};