#pragma once
#include "MovementComponent.h"
#include "TransformComponent.h"
class MovementComponentFrançois:public MovementComponent
{
private:
	
public:
	MovementComponentFrançois();
	void initComponent();
	void update();
	void changeDirection(int direction);
};

