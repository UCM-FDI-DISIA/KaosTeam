#include "MovementComponentFranšois.h"

MovementComponentFranšois::MovementComponentFranšois(TransformComponent* transform):trans(transform)
{
}

void MovementComponentFranšois::initComponent()
{
}

void MovementComponentFranšois::update()
{
}

void MovementComponentFranšois::changeDirection(int direction)
{
	if (speed < 0 && direction>0 || speed > 0 && direction < 0)
		speed* direction;
}
