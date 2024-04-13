#pragma once
#include "../ecs/Entity.h"
class BossSystem
{
	private:
		Entity* boss;
public:
	BossSystem(Entity* fran);
	~BossSystem();
	void initSystem();
	void update();
	void render();
};