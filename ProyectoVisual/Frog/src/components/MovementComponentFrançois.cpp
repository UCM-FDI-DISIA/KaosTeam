#include "MovementComponentFran�ois.h"

MovementComponentFran�ois::MovementComponentFran�ois():trans(nullptr)
{
}

void MovementComponentFran�ois::initComponent()
{
	trans = static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT));
}

void MovementComponentFran�ois::update()
{
}

void MovementComponentFran�ois::changeDirection(int direction)
{
	if (speed < 0 && direction>0 || speed > 0 && direction < 0)
		speed* direction;
}
