#pragma once
#include "MovementComponent.h"
#include "../sdlutils/SDLUtils.h"
#include <iostream>

class FollowPlayerComponent: public MovementComponent
{
protected:
	Vector2D vel;
	int lastTimeMoved;
	int waitTime = 300;
public:
	FollowPlayerComponent(Vector2D pos);
	virtual ~FollowPlayerComponent();
	void FollowPlayer(float x, float y);
	void update() override;
};

