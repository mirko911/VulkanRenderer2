#pragma once

#include <vector>
#include "../GameRoot.hpp"


class DemoMaterial {
private:
	std::vector<int32_t> scenes;
	int32_t mainScene;

	void initBlueWorld(GameRoot& gameRoot);

	std::vector<int32_t> m_transformations;

public:
	void init(GameRoot& gameRoot);
	void run(GameRoot& gameRoot);
	void update(const float fTimeDelta, GameRoot& gameRoot);
};