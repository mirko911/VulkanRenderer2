#pragma once
#include <deque>
#include <unordered_map>
#include <string>
#include <memory>

#include <loguru.hpp>
#include "../defintions.hpp"
#include "../VulkanDevice.hpp"

constexpr int32_t ENTITY_NOT_FOUND = -1;

class HandlerBase {
private:
	std::unordered_map<std::string, int32_t> m_aliases;
	std::string m_debugName;
protected:
	int32_t m_nextID;
	std::deque<int32_t> m_freeIDs;
	int32_t getNextModuleID();
public:
	virtual void init(VulkanDevice& device);
	virtual void update(const float fTimeDelta);
	void setAlias(const int32_t ID, const std::string& alias);
	int32_t getID(const std::string& alias);
	void setDebugName(const std::string& name);
	std::string getDebugName() const;
};