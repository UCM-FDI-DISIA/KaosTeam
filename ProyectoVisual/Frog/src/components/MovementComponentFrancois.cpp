#include "MovementComponentFrancois.h"
#include"../ecs/Entity.h"
#include"../scenes/RoomScene.h"

MovementComponentFrancois::MovementComponentFrancois(int width):pos(BOSS_INIT_POS), //
speed(Vector2D(-ent->getScene()->getMapReader()->getTileSize() / 5, 0)), multiplier(0.2), //
lowerLimit(0), upperLimit(ent->getScene()->getMapReader()->getMapSize().getX()-width)
{
	initComponent();
}

MovementComponentFrancois::~MovementComponentFrancois()
{
}

void MovementComponentFrancois::initComponent()
{
	tr = ent->getComponent<TransformComponent>(TRANSFORM_COMPONENT);
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
	int t = ent->getScene()->getMapReader()->getTileSize();

	tr->setOffsetX(tr->getOffset().getX() + t * speed.getX()*multiplier);
}
