#pragma once
#include "../ecs/Component.h"
#include "../managers/InputManager.h"
class Entity;
class DefenseComponent : public Component
{
private:
	bool defenseActive = false;
	int defenseTime = 50, timeSinceActivation = 0, defenseCooldown = 20;

public:
	void update() override;
	bool defenseActive();
};