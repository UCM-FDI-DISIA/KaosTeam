#pragma once
#include "MovementComponent.h"
#include "TransformComponent.h"
class MovementComponentFran�ois:public MovementComponent
{
private:
	
public:
	MovementComponentFran�ois();
	void initComponent();
	void update();
	void changeDirection(int direction);
};

