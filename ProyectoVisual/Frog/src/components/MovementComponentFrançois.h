#pragma once
#include "MovementComponent.h"
#include "TransformComponent.h"
class MovementComponentFran�ois:public MovementComponent
{
private:
	int speed; //velocidad de fracois
	TransformComponent* trans;
public:
	MovementComponentFran�ois();
	void initComponent();
	void update();
	void changeDirection(int direction);
};

