#include "AttackComponentFrog.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/DataManager.h"
#include "RenderComponentFrog.h"
#include "../utils/Box.h"
#include "ColliderComponent.h"

AttackComponentFrog::AttackComponentFrog() : inputM(InputManager::GetInstance()) {
	distance = 2;
	distanceMoved = 0;
	attackFrameTime = 100;
	lastTimeChanged = 0;
	attackCooldown = 250;

	box = new Box();
}

AttackComponentFrog::~AttackComponentFrog() {
	delete box;
}

void AttackComponentFrog::update()
{
	if (state != 0 && (DataManager::GetInstance()->getFrameTime() - lastTimeChanged) > attackFrameTime) {
		lastTimeChanged = DataManager::GetInstance()->getFrameTime();

		if (state == 1) {
			distanceMoved++;
			if (distanceMoved == distance)
				state++;
		}
		else if (state == 2) {
			distanceMoved--;
			if (distanceMoved < 0)
				state = 0;
		}
	}
}

void AttackComponentFrog::attack()
{
	lastTimeChanged = DataManager::GetInstance()->getFrameTime();
	state = 1;
	distanceMoved = 0;
	static_cast<RenderComponentFrog*>(ent->getRenderComponentFrog())->AttackStart();
}

void AttackComponentFrog::EndAttack()
{
	state = 2;
}

