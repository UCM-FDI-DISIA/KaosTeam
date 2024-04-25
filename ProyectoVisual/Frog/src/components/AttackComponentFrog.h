#pragma once
#include "../ecs/Component.h"
#include "../managers/InputManager.h"
#include "../components/RenderComponentFrog.h"
#include "ColliderComponent.h"

class Box;
class Entity;
class AttackComponentFrog : public Component
{
private:
	int distance , distanceMoved ;
	int attackFrameTime , lastTimeChanged, attackCooldown ;
	//resting = 0, attacking = 1, retracting = 2
	int state = 0;
	InputManager* inputM;
	Box* box;

public:
	AttackComponentFrog();
	virtual ~AttackComponentFrog();
	void update() override;
	int getDistanceMoved() { return distanceMoved; };
	void attack();
	void EndAttack();
	void tongueTouch(Entity* ent, Collider c);
	void UpdateBox(Vector2D casilla, int w, int h);
	void setDistance(int d) { distance = d; }
};

