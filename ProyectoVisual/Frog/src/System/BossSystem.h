#pragma once
#include "../ecs/Entity.h"
class BossSystem
{
	private:
		Entity* boss;
public:
	BossSystem();
	~BossSystem();
	void initSystem();
	void update();
	void render();
};