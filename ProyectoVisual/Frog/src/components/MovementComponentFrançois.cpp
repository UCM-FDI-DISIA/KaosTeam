#include "MovementComponentFran�ois.h"

MovementComponentFran�ois::MovementComponentFran�ois(TransformComponent* transform):trans(transform)
{
}

void MovementComponentFran�ois::initComponent()
{
}

void MovementComponentFran�ois::update()
{
}

void MovementComponentFran�ois::changeDirection(int direction)
{
	if (speed < 0 && direction>0 || speed > 0 && direction < 0)
		speed* direction;
}
