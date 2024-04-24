#pragma once
#include "../ecs/Component.h"
#include "../components/RenderComponentFrog.h"

class Entity;
class Box;
class AttackComponentSnake : public Component {
private:
	int attackDistance, distanceMoved;
	int attackFrameTime, lastTimeChanged, attackCooldown;
	//resting = 0, attacking = 1, retracting = 2
	int state;
	//InputManager* inputM;
	Box* attackBox;
	virtual ~AttackComponentSnake() {
		delete attackBox;
	};
public:
	AttackComponentSnake();
	void update() override;
	int getDistanceMoved() { return distanceMoved; };
	void attack();

};

