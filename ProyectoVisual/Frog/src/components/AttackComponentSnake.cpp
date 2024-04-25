#include "AttackComponentSnake.h"
#include "RenderComponentSnake.h"
#include "../managers/DataManager.h"
#include "ColliderComponent.h"
#include "../utils/Box.h"
#include "../utils/Vector2D.h"

AttackComponentSnake::AttackComponentSnake() {
	attackDistance = 2;
	distanceMoved = 0;
	attackFrameTime = 100;
	lastTimeChanged = 0;
	attackCooldown = 250;
	state = 0;

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
}

void AttackComponentSnake::checkHit(Entity* e, Collider c) {
	if (e->getName() == FROG_ENTITY) {
		cout << "detecta la rana";
	}
}