#pragma once

#include <vector>

class GameRoot;

class DemoBase {
private:
public:
	virtual void init(GameRoot& gameRoot) {};
	virtual void run(GameRoot& gameRoot) {};
	virtual void update(const float fTimeDelta, GameRoot& gameRoot) {};
};