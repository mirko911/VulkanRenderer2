#pragma once

#include <string>

#include <loguru.hpp>
#include "../VulkanDevice.hpp"

#include "../handler/HandlerEvent.hpp"

class GameRoot;

class InputBase {
private:
	int32_t m_moduleID = ENTITY_NOT_FOUND;
	std::string m_debugName = "Generic Input";
public:
	void setModuleID(const int32_t ID);
	int32_t getModuleID() const;

	void setDebugName(const std::string& name);
	std::string getDebugName() const;
public:
	virtual void Init(VulkanDevice& device) {};
	virtual void update(const float fTimeDelta, GameRoot& gameRoot) {};
};
