#pragma once
#include "../ecs/Component.h"
#include "../components/TransformComponent.h"
class MovementComponentFrançois:public Component
{
private:
	int speed; //velocidad de fracois
	TransformComponent* trans;
public:
	MovementComponentFrançois(TransformComponent* transform);
	void initComponent();
	void update();
	void setDirection(int direction);
};

