#pragma once
#include "MovementComponent.h"
#include <iostream>

class FollowPlayerComponent: public MovementComponent
{
protected:
	Vector2D vel;
public:
	FollowPlayerComponent();
	virtual ~FollowPlayerComponent();
	void FollowPlayer(float x, float y);
};

