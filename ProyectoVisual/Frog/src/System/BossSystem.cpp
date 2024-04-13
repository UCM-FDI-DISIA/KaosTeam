#include "BossSystem.h"
#include "../components/AttackComponentFrançois.h"
#include"../components/MovementComponentFrançois.h"
#include "../components/ShadowDetection.h"
#include "../utils/Vector2D.h"

BossSystem::BossSystem(Entity* fran):boss(fran)
{
	initSystem();
}

BossSystem::~BossSystem()
{
}

void BossSystem::initSystem()
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

void BossSystem::update()
{
}

void BossSystem::render()
{
}

void BossSystem::changeDirection(int direction)
{
	move->changeDirection(direction);
}
