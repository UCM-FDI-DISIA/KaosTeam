#pragma once
#include <SDL.h>
#include "../ecs/Component.h"

class Collider;
class Entity;
class Box;
class AttackComponentBasicEnemy : public Component {
private:
	virtual ~AttackComponentBasicEnemy();
	void checkHit(Entity*, Collider);
	bool hitted;
	int damage;
	Uint32 elapsedTime;
public:
	AttackComponentBasicEnemy(int damage);
	void update() override;
	void initComponent() override;
};

