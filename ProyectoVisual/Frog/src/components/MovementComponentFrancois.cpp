#include "MovementComponentFrancois.h"
#include"../ecs/Entity.h"
#include"../scenes/RoomScene.h"

MovementComponentFrancois::MovementComponentFrancois() :pos(BOSS_INIT_POS), //
multiplier(0.2), //
lowerLimit(0)
{
}

MovementComponentFrancois::~MovementComponentFrancois()
{
}

void MovementComponentFrancois::initComponent()
{
	velocity = Vector2D(1, 0);
	upperLimit = ent->getScene()->getMapReader()->getMapSize().getX();
	tr = static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT));
}

void MovementComponentFrancois::checkDirection()
{
	if (isShadowAtLimit(pos)) velocity = velocity * -1;
}

void MovementComponentFrancois::setLowerLimit(short int newLimit)
{
	lowerLimit = newLimit;
}

void MovementComponentFrancois::setSpeed(Vector2D newSpeed)
{
	velocity = newSpeed;
}

void MovementComponentFrancois::setMultiplier(float newMultiplier)
{
	multiplier = newMultiplier;
}

bool MovementComponentFrancois::isShadowAtLimit(Vector2D pos) const
{
	return  tr->getCasilla().getX() <= lowerLimit
		|| tr->getCasilla().getX() >= upperLimit;
}

void MovementComponentFrancois::update()
{
	checkDirection();
	tr->setOffsetX(tr->getOffset().getX()+velocity.getX());
	tr->setCasilla(velocity + tr->getCasilla());
	tr->setOffset({ 0,0 });
	cout << tr->getCasilla();
}
