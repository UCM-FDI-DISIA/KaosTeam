#include "AttackComponentFrog.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/DataManager.h"
#include "RenderComponentFrog.h"

void AttackComponentFrog::update()
{
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

void AttackComponentFrog::attack()
{
	lastTimeChanged = DataManager::GetInstance()->getFrameTime();
	state = 1;
	distanceMoved = 0;
	static_cast<RenderComponentFrog*>(ent->getRenderComponentFrog())->AttackStart();
}
