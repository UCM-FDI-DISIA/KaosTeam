#pragma once
#include "MovementComponent.h"
#include "TransformComponent.h"
class MovementComponentFranšois:public MovementComponent
{
private:
	int speed; //velocidad de fracois
	TransformComponent* trans;
public:
	MovementComponentFranšois();
	void initComponent();
	void update();
	void changeDirection(int direction);
};

