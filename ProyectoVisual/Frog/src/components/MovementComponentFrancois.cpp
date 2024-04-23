#include "MovementComponentFrancois.h"
#include"../ecs/Entity.h"
#include"../scenes/RoomScene.h"

MovementComponentFrancois::MovementComponentFrancois():pos(BOSS_INIT_POS), //
speed(Vector2D(-ent->getScene()->getMapReader()->getTileSize() / 5, 0)), multiplier(0.2), //
lowerLimit(0), upperLimit(ent->getScene()->getMapReader()->getMapSize().getX())
{
}

MovementComponentFrancois::~MovementComponentFrancois()
{
}

void MovementComponentFrancois::checkDirection()
{
	if (isShadowAtLimit(pos)) speed = speed * -1;
}

void MovementComponentFrancois::setLowerLimit(short int newLimit)
{
	lowerLimit = newLimit;
}

void MovementComponentFrancois::setSpeed(Vector2D newSpeed)
{
	speed = newSpeed;
}

void MovementComponentFrancois::setMultiplier(float newMultiplier)
{
	multiplier = newMultiplier;
}

bool MovementComponentFrancois::isShadowAtLimit(Vector2D pos) const
{
	return pos.getX() <= lowerLimit
		|| pos.getX() >= upperLimit;
}

void MovementComponentFrancois::update()
{
	pos = pos + speed*multiplier;
}
