#pragma once
#include "../ecs/Component.h"

class Collider;
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
	virtual ~AttackComponentSnake();
	void checkHit(Entity*, Collider);
	void checkHitWithBody(Entity*, Collider);
	bool hitted;
	int damage;
public:
	AttackComponentSnake();
	void update() override;
	int getDistanceMoved() { return distanceMoved; };
	void attack();
	void UpdateBox(Vector2D casilla, float w, float h);
	void initComponent() override;
};

