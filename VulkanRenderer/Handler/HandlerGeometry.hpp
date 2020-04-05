#pragma once

#include "HandlerBase.hpp"

#include "../Modules/ModuleBase.hpp"

class HandlerGeometry : public HandlerBase{
private:
	std::unordered_map<int32_t, std::unique_ptr<ModuleBase>> m_entities;
public:
	template <typename T, typename ... Args>
	ModuleInfo<T> create(Args&& ... args) {
		const int32_t ID = getNextModuleID();

		m_entities[ID] = std::make_unique<T>(std::forward<Args>(args)...);
		m_entities[ID]->setModuleID(ID);

		return { ID, reinterpret_cast<T*>(m_entities[ID].get()) };
	}

	template <typename T>
	T* get(const int32_t ID ) {
		return reinterpret_cast<T*>(m_entities[ID].get());
	}



	//virtual void init(VulkanDevice& device);
	//virtual void update(const float fTimeDelta);
};