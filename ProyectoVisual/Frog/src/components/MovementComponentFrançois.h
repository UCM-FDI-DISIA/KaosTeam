#pragma once
#include "MovementComponent.h"
class MovementComponentFranšois:public MovementComponent
{
private:
	int speed; //velocidad de fracois
	TransformComponent* trans;
public:
	MovementComponentFranšois(TransformComponent* transform);
	void initComponent();
	void update();
	void changeDirection(int direction);
};

