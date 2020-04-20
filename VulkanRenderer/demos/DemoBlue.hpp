#pragma once

#include <vector>
#include "../GameRoot.hpp"


class DemoBlue {
private:
	std::vector<int32_t> scenes;
	int32_t mainScene;

	void initBlueWorld(GameRoot& gameRoot);

	int32_t sceneUniverse;
	int32_t sceneBlueSky;
public:
	void init(GameRoot& gameRoot);
	void run(GameRoot& gameRoot);
	void update(const float fTimeDelta, GameRoot& gameRoot);
};