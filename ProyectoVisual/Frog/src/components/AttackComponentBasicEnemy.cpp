#include "AttackComponentBasicEnemy.h"
#include "ColliderComponent.h"
#include "../utils/Box.h"
#include "LifeComponent.h"
#include "../sdlutils/SDLUtils.h"

AttackComponentBasicEnemy::AttackComponentBasicEnemy(int d) : damage(d) {
	hitted = false;
}

AttackComponentBasicEnemy::~AttackComponentBasicEnemy() {
};

void AttackComponentBasicEnemy::update() {
	if (hitted && sdlutils().virtualTimer().currTime() > elapsedTime + 3000) {
		hitted = false;
	}
}
void AttackComponentBasicEnemy::initComponent() {
	static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT))->GetTransofmCollider()->AddCall([this](Entity* e, Collider c) {
		checkHit(e, c);
	});
}

void AttackComponentBasicEnemy::checkHit(Entity* e, Collider c) {
	if (!hitted && e->getName() == FROG_ENTITY && c.getName() == TRANSFORM_COLLIDER) {
		elapsedTime = sdlutils().virtualTimer().currTime();
		static_cast<LifeComponent*>(e->getComponent(LIFE_COMPONENT))->hit(damage);
		hitted = true;
	}
}
