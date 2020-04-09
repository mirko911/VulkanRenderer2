#pragma once
#include <vector>
#include <unordered_map>

#include "defintions.hpp"
#include <vulkan/vulkan.hpp>
#include <loguru.hpp>

#include "defintions.hpp"

class GameObjekt
{
private:
	std::vector<int32_t> m_children;
	std::unordered_map<std::type_index, int32_t> m_modules;
	int32_t m_sceneID = ENTITY_NOT_FOUND;
	int32_t m_moduleID = ENTITY_NOT_FOUND;
	std::string m_debugName = "Generic Gameobject";
public:
	void setModuleID(const int32_t ID);
	int32_t getModuleID() const;

	void setSceneID(const int32_t ID);
	int32_t getSceneID() const;

	void setDebugName(const std::string& name);
	std::string getDebugName() const;

	std::unordered_map<std::type_index, int32_t> getModules() const;
	void setModules(const std::unordered_map<std::type_index, int32_t> modules);

	void addChild(const int32_t ID);
	std::vector<int32_t> getChildren() const;
	bool hasChildren();
	void removeChild(const int32_t ID);
	void removeAllChildren(const int32_t ID);

	template <typename T>
	void addModule(const int32_t ID, const bool force = false) {
		const auto typeIndex = getType<T>();

		if (hasModule<T>() && !force) {
			LOG_F(ERROR, "Module %s already exists in %s", typeIndex.name(), getDebugName().c_str());
		}

		m_modules[typeIndex] = ID;
	}

	template <typename T>
	bool hasModule() {
		const auto typeIndex = getType<T>();
		
		return (m_modules.find(typeIndex) != m_modules.end());
	}

	template <typename T>
	int32_t getModule() {
		const auto typeIndex = getType<T>();
		if (!hasModule<T>()) {
			LOG_F(WARNING, "Module %s doesn't exists in %s", typeIndex.name(), getDebugName().c_str());
			return ENTITY_NOT_FOUND;
		}

		return m_modules[typeIndex];
	}




};

