#pragma once
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
const int BOSS_W = 10;
const int BOSS_H = 10;
class BossSystem
{
	private:
		Entity* boss;
		AttackComponentFrançois* attak;
		TransformComponent* franTrans;
		MovementComponentFrançois* move;
		ShadowDetection* detec;
public:
	BossSystem(Entity* fran);
	~BossSystem();
	void initSystem();
	void update();
	void render();
	void changeDirection(int direction);
};