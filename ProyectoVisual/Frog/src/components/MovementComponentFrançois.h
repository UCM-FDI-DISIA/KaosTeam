#pragma once
#include "MovementComponent.h"
class MovementComponentFrançois:public MovementComponent
{
private:
	int speed; //velocidad de fracois
	TransformComponent* trans;
public:
	MovementComponentFrançois(TransformComponent* transform);
	void initComponent();
	void update();
	void changeDirection(int direction);
};

