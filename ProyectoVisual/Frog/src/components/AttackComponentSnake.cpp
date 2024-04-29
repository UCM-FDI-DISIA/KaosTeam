#include "AttackComponentSnake.h"
#include "RenderComponentSnake.h"
#include "../managers/DataManager.h"
#include "ColliderComponent.h"
#include "../utils/Box.h"
#include "../utils/Vector2D.h"
#include "LifeComponent.h"
#include "../components/RenderComponentFrog.h"

AttackComponentSnake::AttackComponentSnake() {
	attackDistance = 2;
	distanceMoved = 0;
	attackFrameTime = 100;
	lastTimeChanged = 0;
	attackCooldown = 250;
	state = 0;
	hitted = false;
	damage = 1;
}

void AttackComponentSnake::update() {
	if (state != 0 && (DataManager::GetInstance()->getFrameTime() - lastTimeChanged) > attackFrameTime) {
		lastTimeChanged = DataManager::GetInstance()->getFrameTime();

		if (state == 1) {
			distanceMoved++;
			if (distanceMoved == attackDistance)
				state++;
		}
		else if (state == 2) {
			distanceMoved--;
			if (distanceMoved < 0) {
				state = 0;
				attackBox->setWidth(0);
				attackBox->setHeight(0);
				hitted = false;
			}
		}
	}
}

void AttackComponentSnake::attack() {
	lastTimeChanged = DataManager::GetInstance()->getFrameTime();
	state = 1;
	distanceMoved = 0;
	static_cast<RenderComponentSnake*>(ent->getRenderComponentSnake())->AttackStart();
}

AttackComponentSnake::~AttackComponentSnake() {
	delete attackBox;
};

void AttackComponentSnake::UpdateBox(Vector2D casilla, float w, float h)
{
	attackBox->setCasilla(casilla);
	attackBox->setWidth(w);
	attackBox->setHeight(h);
}

void AttackComponentSnake::initComponent() {
	attackBox = new Box();
	Collider c = Collider(attackBox);
	c.AddCall([this](Entity* e, Collider c) {
		checkHit(e, c);
		});
	static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT))->AddCollider(c);
}

//Comprueba colisión con la rana, hace daño solo si no ha hecho daño en este atque (variable hitted)
void AttackComponentSnake::checkHit(Entity* e, Collider c) {
	if (!hitted && e->getName() == FROG_ENTITY) {
		static_cast<LifeComponent*>(e->getComponent(LIFE_COMPONENT))->hit(damage);
		hitted = true;
	}
}