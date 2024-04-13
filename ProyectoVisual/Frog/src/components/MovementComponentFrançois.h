#pragma once
#include "../ecs/Component.h"
#include "../components/TransformComponent.h"
class MovementComponentFran�ois:public Component
{
private:
	int speed; //velocidad de fracois
	TransformComponent* trans;
public:
	MovementComponentFran�ois(TransformComponent* transform);
	void initComponent();
	void update();
	void setDirection(int direction);
};

