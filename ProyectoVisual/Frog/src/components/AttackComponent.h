#pragma once
#include "../ecs/Component.h"
class Entity;
class AttackComponent : public Component
{
private:
	int attackDistance = 3, distanceMoved = 1;
	int attackFrameTime = 100, lastTimeChanged=0;
	//resting = 0, attacking = 1, retracting = 2
	int state = 1;

public:
	AttackComponent() {};
	~AttackComponent() {};
	void update() override;
	int getDistanceMoved() { return distanceMoved; }

};

