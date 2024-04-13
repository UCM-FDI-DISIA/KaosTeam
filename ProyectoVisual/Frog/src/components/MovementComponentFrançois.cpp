#include "MovementComponentFrançois.h"

MovementComponentFrançois::MovementComponentFrançois():trans(nullptr)
{
}

void MovementComponentFrançois::initComponent()
{
	trans = static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT));
}

void MovementComponentFrançois::update()
{
}

void MovementComponentFrançois::changeDirection(int direction)
{
	if (speed < 0 && direction>0 || speed > 0 && direction < 0)
		speed* direction;
}
