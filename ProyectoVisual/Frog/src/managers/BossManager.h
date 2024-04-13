#pragma once
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/AttackComponentFran�ois.h"
#include"../components/MovementComponentFran�ois.h"
#include "../components/ShadowDetection.h"
#include "../components/TransformComponent.h"

const float BOSS_W = 10.0;
const float BOSS_H = 10.0;
class BossManager
{
private:
	Entity* boss;
	AttackComponentFran�ois* attak;
	TransformComponent* franTrans;
	MovementComponentFran�ois* move;
	ShadowDetection* detec;
public:
	BossManager(Entity* fran);
	~BossManager();
	void init();
	void update();
	void render();
	void changeDirection(int direction);
};