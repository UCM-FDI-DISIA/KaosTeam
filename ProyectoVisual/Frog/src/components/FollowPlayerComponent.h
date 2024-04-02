#pragma once
#include "MovementComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/DataManager.h"
#include <iostream>

class FollowPlayerComponent: public MovementComponent
{
protected:
	Vector2D vel;
	int lastTimeMoved;
	int waitTime = 3000;
public:
	FollowPlayerComponent(Vector2D pos);
	virtual ~FollowPlayerComponent();
	void update() override;
};

