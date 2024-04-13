#include "BossSystem.h"
#include "../components/AttackComponentFran�ois.h"
#include"../components/MovementComponentFran�ois.h"
#include "../components/ShadowDetection.h"

BossSystem::BossSystem(Entity* fran):boss(fran)
{
}

BossSystem::~BossSystem()
{
}

void BossSystem::initSystem()
{
	AttackComponentFran�ois* attak = new AttackComponentFran�ois();
	MovementComponentFran�ois* move = new MovementComponentFran�ois();
	ShadowDetection* detec = new ShadowDetection();
	boss->addComponent(ATTACK_COMPONENT,attak);
	boss->addComponent(MOVEMENT_COMPONENT, move);
	boss->addComponent(SHADOW_DETECTION, detec);
}

void BossSystem::update()
{
}

void BossSystem::render()
{
}
