#include "BossManager.h"
#include "../utils/Vector2D.h"

BossManager::BossManager(Entity* fran):boss(fran)
{
	init();
}

BossManager::~BossManager()
{
	boss = nullptr;
	attak = nullptr;
	franTrans = nullptr;
	move = nullptr;
	detec = nullptr;
}

void BossManager::init()
{
	attak = new AttackComponentFrançois();
	franTrans = new TransformComponent(new Vector2D(0, 0), BOSS_W, BOSS_H);
	move = new MovementComponentFrançois(franTrans);
	detec = new ShadowDetection();
	boss->addComponent(ATTACK_COMPONENT,attak);
	boss->addComponent(MOVEMENT_COMPONENT, move);
	boss->addComponent(SHADOW_DETECTION, detec);
	boss->addComponent(TRANSFORM_COMPONENT, franTrans);
}

void BossManager::update()
{
}

void BossManager::render()
{
}

void BossManager::changeDirection(int direction)
{
	move->changeDirection(direction);
}
