#include "MovementComponentFranšois.h"

MovementComponentFranšois::MovementComponentFranšois():trans(nullptr)
{
}

void MovementComponentFranšois::initComponent()
{
	trans = static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT));
}

void MovementComponentFranšois::update()
{
}

void MovementComponentFranšois::changeDirection(int direction)
{
	if (speed < 0 && direction>0 || speed > 0 && direction < 0)
		speed* direction;
}
