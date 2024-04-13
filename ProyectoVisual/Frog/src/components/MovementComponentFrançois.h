#pragma once
#include "../ecs/Component.h"
#include "../components/TransformComponent.h"
class MovementComponentFranšois:public Component
{
private:
	int speed; //velocidad de fracois
	TransformComponent* trans;
public:
	MovementComponentFranšois(TransformComponent* transform);
	void initComponent();
	void update();
	void setDirection(int direction);
};

