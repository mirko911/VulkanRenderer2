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

	int32_t sunRotation = ENTITY_NOT_FOUND;
	int32_t earthRotation = ENTITY_NOT_FOUND;;
	int32_t earthOwnRotation = ENTITY_NOT_FOUND;;

	int32_t moonRotation = ENTITY_NOT_FOUND;
	int32_t moonOwnRotation = ENTITY_NOT_FOUND;

	int32_t portalStart;
	int32_t portalEnd;
public:
	void init(GameRoot& gameRoot);
	void run(GameRoot& gameRoot);
	void update(const float fTimeDelta, GameRoot& gameRoot);
};