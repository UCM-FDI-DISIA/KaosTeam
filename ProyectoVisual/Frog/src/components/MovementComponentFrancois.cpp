#include "MovementComponentFrancois.h"
#include "../ecs/Entity.h"
#include "../scenes/RoomScene.h"
#include "BossComponent.h"

MovementComponentFrancois::MovementComponentFrancois() :pos(BOSS_INIT_POS), //
								multiplier(0.2), //
								lowerLimit(0) //
{
}

MovementComponentFrancois::~MovementComponentFrancois()
{
}

void MovementComponentFrancois::initComponent()
{
	velocity = Vector2D(1.0/10, 0);
	tr = static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT));

	upperLimit = ent->getScene()->getMapReader()->getMapSize().getX() - (tr->getWidth() / TILE_SIZE);
}

void MovementComponentFrancois::update()
{
	setDirection();
	if (!static_cast<BossComponent*>(ent->getComponent(BOSS_COMPONENT))->isFlonkAttacking()
			&& !static_cast<BossComponent*>(ent->getComponent(BOSS_COMPONENT))->isDetectingFlonk()) {
		
		tr->setOffsetX(tr->getOffset().getX() + velocity.getX());
		tr->setCasilla(velocity + tr->getCasilla());
		tr->setOffset({ -tr->getWidth() / 2,-tr->getHeight() / 2 });
	}
}
