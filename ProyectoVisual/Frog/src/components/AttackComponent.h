#pragma once
#include "../ecs/Component.h"
#include "../managers/InputManager.h"
class Entity;
class AttackComponent : public Component
{
private:
	int attackDistance = 2, distanceMoved = 0;
	int attackFrameTime = 100, lastTimeChanged=0, attackCooldown =250;
	//resting = 0, attacking = 1, retracting = 2
	int state = 0;
	InputManager* inputM;

public:
	AttackComponent(): inputM(InputManager::GetInstance()) {};
	~AttackComponent() {};
	void update() override;
	int getDistanceMoved() { return distanceMoved; }

};

