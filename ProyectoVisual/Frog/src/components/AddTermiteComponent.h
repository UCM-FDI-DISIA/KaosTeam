#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
class AddTermiteComponent: public Component
{
public:
	AddTermiteComponent(Vector2D pos) : spawnPos(pos) {};
	void update() override;

private:
	Vector2D spawnPos;
	int lastTimeGenerated, waitTime = 500;

};

