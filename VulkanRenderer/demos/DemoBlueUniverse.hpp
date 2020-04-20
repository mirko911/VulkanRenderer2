#pragma once

#include <vector>
#include "../GameRoot.hpp"


class DemoBlueUniverse {
private:
	std::vector<int32_t> scenes;
	int32_t mainScene;

	void initBlueWorld(GameRoot& gameRoot);
	void initUniverse(GameRoot& gameRoot);

	int32_t sceneUniverse;
	int32_t sceneBlueSky;

	int32_t m_sunTransformation = ENTITY_NOT_FOUND;
	int32_t m_earthTransformation = ENTITY_NOT_FOUND;;
	int32_t m_moonTransformation = ENTITY_NOT_FOUND;;

	int32_t m_earthNode1Transformation = ENTITY_NOT_FOUND;
	int32_t m_moonNode1Transformation = ENTITY_NOT_FOUND;

	int32_t portalStart;
	int32_t portalEnd;
public:
	void init(GameRoot& gameRoot);
	void run(GameRoot& gameRoot);
	void update(const float fTimeDelta, GameRoot& gameRoot);
};