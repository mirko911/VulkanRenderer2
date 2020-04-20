#pragma once
#include "DemoBase.hpp"
#include <vector>
#include "../GameRoot.hpp"


class DemoMaterial : public DemoBase {
private:
	std::vector<int32_t> scenes;
	int32_t mainScene;

	void initBlueWorld(GameRoot& gameRoot);

	std::vector<int32_t> m_transformations;

public:
	void init(GameRoot& gameRoot) override;
	void run(GameRoot& gameRoot) override;
	void update(const float fTimeDelta, GameRoot& gameRoot) override;
};