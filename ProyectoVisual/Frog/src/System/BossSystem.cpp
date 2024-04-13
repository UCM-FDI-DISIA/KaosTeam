#include "BossSystem.h"
#include "../components/AttackComponentFrançois.h"
#include"../components/MovementComponentFrançois.h"
#include "../components/ShadowDetection.h"

BossSystem::BossSystem(Entity* fran):boss(fran)
{
}

BossSystem::~BossSystem()
{
}

void BossSystem::initSystem()
{
	AttackComponentFrançois* attak = new AttackComponentFrançois();
	MovementComponentFrançois* move = new MovementComponentFrançois();
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
