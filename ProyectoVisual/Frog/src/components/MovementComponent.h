#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
class MovementComponent
{
protected:
	Vector2D pos;
public:
	MovementComponent(float x, float y);
	virtual ~MovementComponent();
};

