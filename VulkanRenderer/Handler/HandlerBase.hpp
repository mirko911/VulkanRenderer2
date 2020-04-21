#pragma once
#include <deque>
#include <unordered_map>
#include <string>
#include <memory>

#include <loguru.hpp>
#include "../defintions.hpp"
#include "../VulkanDevice.hpp"

class GameRoot;

class HandlerBase {
private:
	//List of aliases
	std::unordered_map<std::string, int32_t> m_aliases;
protected:
	//Next free ID
	int32_t m_nextID;

	//List of unused free ID's
	std::deque<int32_t> m_freeIDs;

	//Returns the ModuleID
	int32_t getNextModuleID();

	//Debug Name
	std::string m_debugName = "Generic Handler";
public:
	//Empty Init-Method
	virtual void init(VulkanDevice& device);

	//Empty Update-Method
	virtual void update(const float fTimeDelta, GameRoot& gameRoot);

	//Adds alias for a given ID
	void addAlias(const int32_t ID, const std::string& alias);
	
	//Removes alias from list
	void removeAlias(const std::string& alias);

	//Removes all aliases which belong to a given ID
	void removeAliases(const int32_t ID);

	void removeAliases();

	//Returns ID which belongs to a given alias
	int32_t getID(const std::string& alias);

	//Sets name of the Handler
	void setDebugName(const std::string& name);

	//Returns the name of the handler
	std::string getDebugName() const;

	void clear();
};