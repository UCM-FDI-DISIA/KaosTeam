#include "AttackComponentSnake.h"
#include "RenderComponentSnake.h"
#include "../managers/DataManager.h"

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
			if (distanceMoved < 0)
				state = 0;
		}
	}
}

void AttackComponentSnake::attack() {
	lastTimeChanged = DataManager::GetInstance()->getFrameTime();
	state = 1;
	distanceMoved = 0;
	static_cast<RenderComponentSnake*>(ent->getRenderComponentSnake())->AttackStart();
}
