#pragma once
#include "MovementComponent.h"
#include "TransformComponent.h"
class MovementComponentFrançois:public MovementComponent
{
private:
	int speed; //velocidad de fracois
	TransformComponent* trans;
public:
	MovementComponentFrançois();
	void initComponent();
	void update();
	void changeDirection(int direction);
};

