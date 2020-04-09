#pragma once

#include <utility>

#include "HandlerBase.hpp"

#include "../Camera.hpp"

class HandlerCamera : public HandlerBase{
private:
	std::unordered_map<int32_t, std::unique_ptr<Camera>> m_entities;
public:
	//HandlerTransformation();

	template <typename... Args>
	ModuleInfo<Camera> create(Args&& ... args) {
		const int32_t ID = getNextModuleID();

		m_entities[ID] = std::make_unique<Camera>(std::forward<Args>(args)...);
		m_entities[ID]->setModuleID(ID);

		return { ID, reinterpret_cast<Camera*>(m_entities[ID].get()) };
	}

	Camera* get(const int32_t ID ) {
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

	std::unordered_map<int32_t, std::unique_ptr<Camera>>& getAll();


	//virtual void init(VulkanDevice& device);
	//virtual void update(const float fTimeDelta);
};