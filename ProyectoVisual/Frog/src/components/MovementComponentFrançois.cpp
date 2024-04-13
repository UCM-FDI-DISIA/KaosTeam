#include "MovementComponentFrançois.h"

MovementComponentFrançois::MovementComponentFrançois(TransformComponent* transform):trans(transform)
{
}

void MovementComponentFrançois::initComponent()
{
}

void MovementComponentFrançois::update()
{
}

void MovementComponentFrançois::changeDirection(int direction)
{
	if (speed < 0 && direction>0 || speed > 0 && direction < 0)
		speed* direction;
}
