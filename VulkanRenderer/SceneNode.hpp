#pragma once


#include "modules/ModuleTransformation.hpp"


class SceneNode {
private:
	int32_t m_transformationID = ENTITY_NOT_FOUND;
	std::vector<int32_t> m_gameObjects;
	std::vector<int32_t> m_childs;
	int32_t m_moduleID = ENTITY_NOT_FOUND;
	std::string m_debugName = "Generic SceneNode";
public:
	void setModuleID(const int32_t ID);
	int32_t getModuleID() const;

	void setDebugName(const std::string& name);
	std::string getDebugName() const;

	void setTransformationID(const int32_t ID);
	void addGameObject(const int32_t ID);
	void addChild(const int32_t ID);
	std::vector<int32_t>& getChilds();
	std::vector<int32_t>& getGameObjects();
	int32_t getTransformationID();

	void update(const float fTimeDelta, GameRoot& gameRoot);
	void traverse2(GameRoot& gameRoot, SceneNode* parentNode, Mat4& globalMat);
};