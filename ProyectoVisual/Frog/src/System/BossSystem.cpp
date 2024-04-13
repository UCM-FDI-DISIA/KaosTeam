#include "BossSystem.h"
#include "../components/AttackComponentFranšois.h"
#include"../components/MovementComponentFranšois.h"
#include "../components/ShadowDetection.h"

BossSystem::BossSystem(Entity* fran):boss(fran)
{
}

BossSystem::~BossSystem()
{
}

void BossSystem::initSystem()
{
	AttackComponentFranšois* attak = new AttackComponentFranšois();
	MovementComponentFranšois* move = new MovementComponentFranšois();
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
