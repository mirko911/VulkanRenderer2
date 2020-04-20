#pragma once
#include "DemoBase.hpp"

#include <vector>
#include "../GameRoot.hpp"


class DemoBlue : public DemoBase {
private:
	std::vector<int32_t> scenes;
	int32_t mainScene;

	void initBlueWorld(GameRoot& gameRoot);

	int32_t sceneUniverse;
	int32_t sceneBlueSky;
public:
	void init(GameRoot& gameRoot) override;
	void run(GameRoot& gameRoot) override;
	void update(const float fTimeDelta, GameRoot& gameRoot) override;
};