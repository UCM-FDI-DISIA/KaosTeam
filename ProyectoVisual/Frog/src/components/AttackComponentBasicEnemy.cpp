#include "AttackComponentBasicEnemy.h"
#include "ColliderComponent.h"
#include "LifeComponent.h"
#include "DefenseComponent.h"
#include "../sdlutils/SDLUtils.h"

AttackComponentBasicEnemy::AttackComponentBasicEnemy(int d) : damage(d) {
	hitted = false;
	elapsedTime = 0;
}

AttackComponentBasicEnemy::~AttackComponentBasicEnemy() {
};

void AttackComponentBasicEnemy::update() {
	//cuando pasa el tiempo de espera, puede volver a atacar a la rana
	if (hitted && sdlutils().virtualTimer().currTime() > elapsedTime + WAIT_ATTACK) {
		hitted = false;
	}
}
void AttackComponentBasicEnemy::initComponent() {
	static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT))->GetTransformCollider()->AddCall([this](Entity* e, Collider c) {
		checkHit(e, c);
	});
}
//comprueba la colision entre el enemigo y la rana
void AttackComponentBasicEnemy::checkHit(Entity* e, Collider c) {
	if(e->getName() == FROG_ENTITY)
	{
		if (!hitted && !static_cast<DefenseComponent*>(e->getComponent(DEFENSE_COMPONENT))->getDefenseActive() && c.getName() == TRANSFORM_COLLIDER) {
			elapsedTime = sdlutils().virtualTimer().currTime();
			static_cast<LifeComponent*>(e->getComponent(LIFE_COMPONENT))->hit(damage);
			hitted = true;
		}
	}
}
