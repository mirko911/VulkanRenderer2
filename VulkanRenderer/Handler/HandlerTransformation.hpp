#pragma once

#include <utility>

#include "HandlerBase.hpp"

#include "../Modules/ModuleBase.hpp"
#include "../Modules/ModuleTransformation.hpp"

#include "../GameObjekt.hpp"


class HandlerTransformation : public HandlerBase{
private:
	std::unordered_map<int32_t, std::unique_ptr<ModuleTransformation>> m_entities;
public:
	//HandlerTransformation();

	template <typename... Args>
	ModuleInfo<ModuleTransformation> create(Args&& ... args) {
		const int32_t ID = getNextModuleID();

		m_entities[ID] = std::make_unique<ModuleTransformation>(std::forward<Args>(args)...);
		m_entities[ID]->setModuleID(ID);

		return { ID, reinterpret_cast<ModuleTransformation*>(m_entities[ID].get()) };
	}

	ModuleTransformation* get(const int32_t ID ) {
		if (!has(ID)) {
			LOG_F(ERROR, "Entity (ID %i) doesn't exist in %s", ID, getDebugName().c_str());
		}

		return m_entities[ID].get();
	}

	ModuleTransformation* get(GameObjekt* gameobject) {
		if (!gameobject->hasModule<ModuleTransformation>()) {
			LOG_F(ERROR, "Entity doesn't have module %s", gameobject->getDebugName().c_str());
		}
		const int32_t ID = gameobject->getModule<ModuleTransformation>();
		return m_entities[ID].get();
	}



	bool has(const int32_t ID) {
		return (m_entities.find(ID) != m_entities.end());
	}

	void remove(const int32_t ID) {
		m_entities.erase(ID);
	}

	std::unordered_map<int32_t, std::unique_ptr<ModuleTransformation>>& getAll();


	void init(VulkanDevice& device);
	void update(const float fTimeDelta, GameRoot& gameRoot);
};