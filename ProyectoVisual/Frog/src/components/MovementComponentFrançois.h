#pragma once
#include "MovementComponent.h"
#include "TransformComponent.h"
class MovementComponentFranšois:public MovementComponent
{
private:
	
public:
	MovementComponentFranšois();
	void initComponent();
	void update();
	void changeDirection(int direction);
};

