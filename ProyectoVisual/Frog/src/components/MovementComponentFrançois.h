#pragma once
#include "MovementComponent.h"
class MovementComponentFran�ois:public MovementComponent
{
private:
	int speed; //velocidad de fracois
	TransformComponent* trans;
public:
	MovementComponentFran�ois(TransformComponent* transform);
	void initComponent();
	void update();
	void changeDirection(int direction);
};

